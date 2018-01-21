#include <iostream>
#include "cGraph.h"
using namespace std;

int main() {
  cGraph<int, float> myGraph = cGraph<int, float>();

  size_t n0 = myGraph.addVertex(10);
  size_t n1 = myGraph.addVertex(1);
  size_t n2 = myGraph.addVertex(12);
  size_t n3 = myGraph.addVertex(-4);
  size_t n4 = myGraph.addVertex(10);

  myGraph.addEdge(n1, n2, 0.8);
  myGraph.addEdge(n1, n3, 0.6);
  myGraph.addEdge(n2, n1, -0.8);
  myGraph.addEdge(n0, n4, 123.66);

  cout << myGraph[0] << endl;
  cout << myGraph[1] << endl;
  cout << myGraph[2] << endl;
  cout << myGraph[3] << endl;
  cout << myGraph[4] << endl;
  cout << endl;


  return 0;
}
