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

BFS::BFS(const Graph &g) : g(g), mark(g.getNumVertices(), -1),
                           parents(g.getNumVertices(), 0), count(0)
{
   // startSearch();
} // end constructor

void BFS::startSearch(int startVertex, void visit(int &))
{
   //   for (int v = 0; v < g.getNumVertices(); v++)
   //      if (mark[v] == -1)
   //         search(Edge(v, v, 0));

   search(Edge(startVertex, startVertex, 0), visit);
} // end startSearch

void BFS::search(Edge e, void visit(int &))
{
   // create a queue to push edges
   queue<Edge> q;

   map<int, int> m; // holds adjacency list of current vertex
   map<int, int>::iterator iter;

   q.push(e);

   while (!q.empty())
   {
      // get the edge at the front if the queue
      e = q.front();

      // pop the edge off the queue
      q.pop();

      // if the vertex w has not visited yet, visit it
      if (mark[e.w] == -1)
      {
         int v = e.v, w = e.w, weight = e.weight;
         mark[w] = count++; // mark w visited
         parents[w] = v;    // store w's parent
         visit(w);          // display the vertex

         // go through adjacency list of w
         m = g.adjList[w];
         for (iter = m.begin(); iter != m.end(); iter++)
            // if w's neighbor vertices have not been visited,
            // push the edge on the queue
            if (mark[iter->first] == -1)
               q.push(Edge(w, iter->first, iter->second));
      } // end if
   }    // end while
} // end search
// End of implementation file
