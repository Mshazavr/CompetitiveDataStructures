#include <iostream>
#include "segmentTree.h"

struct myData {
  int val;
  int dif;
  int s, e;
public:
  myData(): val{0}, dif{0}, s{0}, e{0} {}
  myData(int val, int dif, int s, int e): val{val}, dif{dif}, s{s}, e{e} {}
};

myData myIdentity = myData();

myData myMerge(const myData &A, const  myData &B) {
  myData result;
  result.val = A.val + B.val;
  result.s = A.s;
  result.e = B.e;
  return result;
}

void myPush(myData &T, myData &A, myData &B) {
  T.val += T.dif * (T.e - T.s + 1);
  A.dif += T.dif;
  B.dif += T.dif;
  T.dif = 0;
}

void myModify(myData &A, const myData &B) {
  A.dif += B.dif;
}

std::vector<myData> arr;

int main() {
  arr.push_back(myData(1, 0, 0, 0));
  arr.push_back(myData(13, 0, 1, 1));
  arr.push_back(myData(-4, 0, 2, 2));
  arr.push_back(myData(3, 0, 3, 3));
  arr.push_back(myData(4, 0, 4, 4));
  arr.push_back(myData(2, 0, 5, 5));
  
  segmentTree<myData> myTree(myMerge, myPush, myModify, myIdentity, arr.begin(), arr.end());

  myData x = myTree.query(1, 3);
  std::cout<<x.val<<std::endl;

  myTree.modify(2, 4, myData(0, 10, 0, 0));
  x = myTree.query(0, 3);
  std::cout<<x.val<<std::endl;
  
  return 0;
}
