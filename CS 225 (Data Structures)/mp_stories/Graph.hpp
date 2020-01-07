#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::numVertices() const {
  return vertexMap.size();
}


/**
* The degree of the vertex. For directed: Sum of in-degree and out-degree
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  std::list<edgeListIter> edgeList = adjList.at(v.key());

  return edgeList.size();

}


/**
* Inserts a Vertex into the Graph.
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  
  V & v = *(new V(key));
  vertexMap.insert({key,v});
  adjList.emplace(key,std::list<edgeListIter>());

  return v;
  

}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  auto adj_vertices = adjList.find(key)->second;
  for (auto& edge : adj_vertices){
    removeEdge(edge);
  }
  vertexMap.erase(key);
}


/**
* Inserts an Edge into the Graph.
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  
  E & e = *(new E(v1, v2));

  edgeList.push_front(E_byRef(e));
  edgeListIter new_edge = edgeList.begin();
  adjList.find(v1.key())->second.push_front(new_edge);
  adjList.find(v2.key())->second.push_front(new_edge);

  return e;
}


/**
* Removes an Edge from the Graph. Consider both the undirected and directed cases.
* min(degree(key1), degree(key2))
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {  

  std::list<edgeListIter>& key1_ = adjList.find(key1)->second;
  std::list<edgeListIter>& key2_ = adjList.find(key2)->second;

  std::list<edgeListIter> m;

  if (key1_.size() >  key2_.size()) m = key2_;
  else m = key1_;

  for (auto it_ = m.begin(); it_ != m.end(); it_++){

    if ((*it_)->get().source().key() == key1 &&  (*it_)->get().dest().key() == key2)
    removeEdge(*it_);
    if (!(*it_)->get().directed()){
          if ((*it_)->get().source().key() == key2 &&  (*it_)->get().dest().key() == key1) 
          removeEdge(*it_);
    }
  }

}


/**
* Removes an Edge from the Graph given by the location of the given iterator into the edge list.
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {

  std::list<edgeListIter>& key1_ = adjList.find(it->get().source().key())->second;
  
  std::list<edgeListIter>& key2_ = adjList.find(it->get().dest().key())->second;

  for (auto it_ = key1_.begin(); it_ != key1_.end(); it_++){
    if (*it_ == it) key1_.erase(it_);
    }
  
  for (auto it_ = key2_.begin(); it_ != key2_.end(); it_++){
        if (*it_ == it) key2_.erase(it_);
  }
  edgeList.erase(it);
}


/**
* Return the list of incident edges from a given vertex.
* For the directed case, consider all edges that has the vertex as either a source or destination.
* @param key The key of the given vertex
* @return The list edges (by reference) that are adjacent to the given vertex
*/
template <class V, class E>  
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  std::list<std::reference_wrapper<E>> edges;
  for (auto& edge_iter : adjList.find(key)->second){
    edges.push_back(*edge_iter);
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another. Consider both the undirected and directed cases.
* When the graph is directed, v1 and v2 are only adjacent if there is an edge from v1 to v2.
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/  
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {

   if(adjList.at(key1).size() < adjList.at(key2).size()){
    for(edgeListIter it : adjList.at(key1)){
      if((*it).get().dest().key() == key2){
        return true;
      }
    }
  }

  else{
    for(edgeListIter it : adjList.at(key2)){
      
      if((*it).get().source().key() == key1){
        return true;
      }
    }
  }

  return false;

}
