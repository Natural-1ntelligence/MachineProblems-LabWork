#include <queue>
#include <algorithm>
#include <string>
#include <list>

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path;
  std::unordered_map<std::string , std::string> mymaps;     //for mapping parents
  bool found = false;                                       //Set found to false
  std::queue<std::string> myqueue;
  myqueue.push(start);
  mymaps.insert({start,start});                             //maps to itself
  while(!found)
  {
    std::string traverser = myqueue.front();                //popping front
    myqueue.pop();
    std::list<std::reference_wrapper<E>> edgeList = incidentEdges(traverser);
    for(Edge & e : edgeList)
    {
      if(e.dest().key() == end) {found = true;}               //Set found to true

      if(e.source().key() == end) { found = true; }           //Set found to true

      if(mymaps.find(e.dest().key()) == mymaps.end())         //Case when not in map
      {
        myqueue.push( e.dest().key() );                       //pushing all neighbors to myqueue
        mymaps.insert({e.dest().key(),e.source().key()});
      }
      if(mymaps.find(e.source().key()) == mymaps.end())       //Case when not in map
      {
        myqueue.push(e.source().key());                       //Pushing all neighbors to myqueue
        mymaps.insert({e.source().key(),e.dest().key()});
      }
    }
  }
  bool done = false;                                          //backtracking, Set Done to False
  std::string hold = end;
  while(!done)
  {
    if(hold==start) { done = true; }                          //Set Done to true
    path.push_front(hold);
    hold = mymaps.at(hold);
  }

  return path;
}
