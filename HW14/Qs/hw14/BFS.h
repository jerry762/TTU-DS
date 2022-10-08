/** @file BFS.h */

#include <queue>
#include "Graph.h"

using namespace std;

typedef void (*FunctionType)(int aVertex);

/** @class BFS
 *  A breadth-first search of the Graph class. */
class BFS
{
protected:
   const Graph& g;

   /** Used to mark vertices as visited. */
   int count;

   /** Marked vertices. */
   vector<int> mark;

   /** Parents of each vertex. */
//   vector<int> parents;

   /** Searches the adjacency list of each vertex breadth first.
    * @pre  The edge exists in the graph.
    * @post Performs a breadth first search of the adjacency list
    *       of vertex w in Edge e. */
   void search(Edge e, void visit(int &) );

 public:
   /** Constructor
    * @pre The graph exists.
    * @post Initializes arguments and starts the breadth-first
    *       search. */
   BFS(const Graph& g);

   /** Searches each unvisited vertex
    * @pre  The edge exists in the graph.
    * @post Starts a breadth first search with each unvisited
    *       vertex. */
   void startSearch(int startVertex,  void visit(int &));
   vector<int> parents;
}; // end BFS
// End of header file
