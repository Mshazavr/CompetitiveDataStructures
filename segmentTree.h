#ifndef __SEGMENTTREE__
#define __SEGMENTTREE__

#include <iostream>
#include <vector>

template<typename Data>
class segmentTree {
  Data (*mergeFn)(const Data &, const Data &);
  void (*pushFn)(Data &, Data &, Data &);
  void (*modifyFn)(Data &, const Data &);
  
  class stNode {
    std::unique_ptr<stNode> leftChild, rightChild;
    Data value;

 public:

    stNode(stNode *leftChild, stNode *rightChild, Data value);
    stNode(const stNode &other);
    stNode(stNode &&other);
    stNode &operator=(const stNode &other);
    stNode &operator=(stNode &&other);
    ~stNode() = default;

    void push(void (*pushFn)(Data &, Data &, Data &));
    void update(Data (*mergeFn)(const Data &, const Data &));
    void modify(void (*modifyFn)(Data &, const Data &), const Data &val);

    friend class segmentTree;
  };

  std::unique_ptr<stNode> root;
  size_t length;
  std::vector<Data> values;
  const Data Identity;

public:

  template<typename Iter>
  segmentTree(Data (*mergeFn)(const Data &, const Data &), void (*pushFn)(Data &, Data &, Data &), void (*modifyFn)(Data &, const Data &), Data Identity, Iter begin, Iter end);
  segmentTree(const segmentTree &other);
  segmentTree(segmentTree && other);
  segmentTree &operator=(const segmentTree &other);
  segmentTree &operator=(segmentTree &&other);
  ~segmentTree() = default;

  void modify(ptrdiff_t left, ptrdiff_t right, Data val) { modifyH(root.get(), 0, length - 1, left, right, val); }
  Data query(ptrdiff_t left, ptrdiff_t right) const { return queryH(root.get(), 0, length - 1, left, right); }
  //Data query(ptrdiff_t left, ptrdiff_t right) const { int z; std::cin >> z; return Identity; }

private:

  stNode *buildH(ptrdiff_t s, ptrdiff_t e);
  void modifyH(stNode *nd, ptrdiff_t s, ptrdiff_t e, ptrdiff_t l, ptrdiff_t r, Data val);
  Data queryH(stNode *nd, ptrdiff_t s, ptrdiff_t e, ptrdiff_t l, ptrdiff_t r) const;

};

// ******************************** //
// * stNode class implementations * //
// ******************************** //

// * Constructor/Destructor implementations  * //

template<typename Data>
segmentTree<Data>::stNode::stNode(stNode *leftChild, stNode *rightChild, Data value):
  leftChild{std::unique_ptr<stNode>{leftChild}}, 
  rightChild{std::unique_ptr<stNode>{rightChild}}, 
  value{value} {}

template<typename Data>
segmentTree<Data>::stNode::stNode(const stNode &other):
  leftChild{std::unique_ptr<stNode>(new stNode(*other.leftChild.get()))},
  rightChild{std::unique_ptr<stNode>(new stNode(*other.rightChild.get()))}, 
  value{other.value} {} 

template<typename Data>
segmentTree<Data>::stNode::stNode(stNode &&other):
  leftChild{std::move(other.leftChild)},
  rightChild{std::move(other.rightChild)}, 
  value{std::move(other.value)} {}
  
template<typename Data>
typename segmentTree<Data>::stNode &segmentTree<Data>::stNode::operator=(const stNode &other) {
  std::unique_ptr<stNode> temp1 = std::move(leftChild);
  std::unique_ptr<stNode> temp2 = std::move(rightChild);
  leftChild = std::unique_ptr<stNode>(new stNode(*other.leftChild().get()));
  rightChild = std::unique_ptr<stNode>(new stNode(*other.rightChild().get()));
  value = other.value;
}

template<typename Data>
typename segmentTree<Data>::stNode &segmentTree<Data>::stNode::operator=(stNode &&other) {
  leftChild = std::move(other.leftChild);
  rightChild = std::move(other.rightChild);
  value = std::move(other.value);
}

// * Other implementations * //

template<typename Data>
void segmentTree<Data>::stNode::push(void (*pushFn)(Data &, Data &, Data &)) { 
  Data dummy;
  pushFn(this->value, leftChild ? leftChild->value : dummy, 
                 rightChild ? rightChild->value : dummy);
}

template<typename Data>
void segmentTree<Data>::stNode::update(Data (*mergeFn)(const Data &, const Data &)) { 
  if(leftChild) value = mergeFn(leftChild->value, rightChild->value);
}

template<typename Data>
void segmentTree<Data>::stNode::modify(void (*modifyFn)(Data &, const Data &), const Data &val) { 
  modifyFn(value, val);
}

// *************************************** //
// * End of stNode class implementations * //
// *************************************** //

// ************************************* //
// * segmentTree class implementations * //
// ************************************* //

// * Constructor/Destructor implementations * //

template<typename Data>
template<typename Iter>
segmentTree<Data>::
segmentTree(Data (*mergeFn)(const Data &, const Data &), void (*pushFn)(Data &, Data &, Data &), void (*modifyFn)(Data &, const Data &), Data Identity, Iter begin, Iter end):
  mergeFn{mergeFn}, pushFn{pushFn}, modifyFn{modifyFn}, Identity{Identity} {
  Iter temp = begin;
  while(temp != end) {
    values.push_back((*temp));
    ++temp;
    ++length;
  }
  root = std::unique_ptr<stNode>{buildH(0, length - 1)};
}

template<typename Data>
segmentTree<Data>::segmentTree(const segmentTree &other): 
  mergeFn{other.mergeFn}, 
  pushFn{other.pushFn},
  modifyFn{other.modifyFn}, 
  root{std::unique_ptr<stNode>(new stNode(*other.root.get()))}, 
  length{other.length},
  values{other.values},
  Identity{other.Identity} {}

template<typename Data>
segmentTree<Data>::segmentTree(segmentTree &&other): 
  mergeFn{std::move(other.mergeFn)},
  pushFn{std::move(other.pushFn)}, 
  modifyFn{std::move(other.modifyFn)}, 
  root{std::move(other.root)}, 
  length{other.length}, 
  values{std::move(other.values)},
  Identity{std::move(other.identity)} {}
  
template<typename Data>
segmentTree<Data> &segmentTree<Data>::operator=(const segmentTree &other) {
  mergeFn = other.mergeFn;
  pushFn = other.pushFn;
  modifyFn = other.modifyFn;
  std::unique_ptr<stNode> temp1 = std::move(root); root = std::unique_ptr<stNode>(new stNode(*other.root.get()));
  length = other.length;
  values = other.values;
  Identity = other.Identity;
}
 
template<typename Data>
segmentTree<Data> &segmentTree<Data>::operator=(segmentTree &&other) {
  mergeFn = std::move(other.mergeFn);
  pushFn = std::move(other.pushFn);
  modifyFn = std::move(other.modifyFn);
  root = std::move(other.root);
  length = other.length;
  values = std::move(other.values);
  Identity = std::move(other.Identity);
}

// * Other implementations * //

template<typename Data>
typename segmentTree<Data>::stNode *segmentTree<Data>::buildH(ptrdiff_t s, ptrdiff_t e) {
  ptrdiff_t m = (s + e) / 2;
  if(s == e) return new stNode(nullptr, nullptr, values[m]);
  stNode *temp1 = buildH(s, m);
  stNode *temp2 = buildH(m + 1, e);
  stNode *result = new stNode(temp1, temp2, Identity);
  result->update(mergeFn);
  return result;
}

template<typename Data>
void segmentTree<Data>::modifyH(stNode *nd, ptrdiff_t s, ptrdiff_t e, ptrdiff_t l, ptrdiff_t r, Data val) {
  ptrdiff_t m = (s + e) / 2;
  nd->push(pushFn);
  if(l > r) return;
  if(s == l && e == r) {
    nd->modify(modifyFn, val);
    nd->push(pushFn);
    return;
  }

  modifyH(nd->leftChild.get(), s, m, l, std::min(r, m), val);
  modifyH(nd->rightChild.get(), m + 1, e, std::max(l, m + 1), r, val);
  nd->update(mergeFn);
}

template<typename Data>
Data segmentTree<Data>::queryH(stNode *nd, ptrdiff_t s, ptrdiff_t e, ptrdiff_t l, ptrdiff_t r) const {
  ptrdiff_t m = (s + e) / 2;
  nd->push(pushFn);
  if(l > r) return Identity;
  if(s == l && e == r) return nd->value;

  return mergeFn(queryH(nd->leftChild.get(), s, m, l, std::min(r, m)),
                 queryH(nd->rightChild.get(), m + 1, e, std::max(l, m + 1), r));
}

// ******************************************** //
// * End of segmentTree class implementations * //
// ******************************************** //

#endif /* __SEGMENTTREE__ */
 
