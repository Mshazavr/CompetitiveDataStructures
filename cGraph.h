#ifndef __CGRAPH__
#define __CGRAPH__

#include <iostream>
#include <vector>

template<typename vData, typename eData>
class cGraph {
  std::vector< std::vector< size_t > > edges;
  std::vector< std::vector< eData > > edgeValues;
  std::vector < vData > vertices;
public:
  cGraph(): 
    edges{std::vector< std::vector< size_t > >()}, 
    edgeValues{std::vector< eData >()},
    vertices{std::vector < vData >()} {}
  cGraph(const cGraph &other) = default;
  cGraph(cGraph &&other) = default;
  cGraph &operator=(const cGraph &other) = default;
  cGraph &operator=(cGraph &&other) = default;
  ~cGraph() {}

  size_t addVertex(vData A) { 
    size_t result = vertices.size(); 
    vertices.push_back(A); 
    edges.push_back( std::vector< size_t >() ); 
    edgeValues.push_back( std::vector< eData >() );
    return result;
  }
  
  void addEdge(size_t A, size_t B, eData E) { edges[A].push_back(B); edgeValues[A].push_back(E); }

  vData &operator[](size_t idx) { return vertices[idx]; }
  
  const vData &operator[](size_t idx) const { return vertices[idx]; }
  
  const std::vector< size_t > &sEdges(size_t idx) const { return edges[idx]; } 

  eData &operator()(int A, int B) { return edgeValues[A][B]; }

};

#endif 