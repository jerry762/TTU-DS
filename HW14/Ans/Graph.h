/** @file Graph.h */

#include <vector>
#include <list>
#include <map>
#include "Edge.h"

using namespace std;

/** An adjacency list representation of an undirected,
 * weighted graph. */
class Graph
{
public:
   int numVertices;   /** Number of vertices in the graph. */
   int numEdges;      /** Number of edges in the graph. */

   /** Adjacency list representation of the graph;
    * the map pair consists of the second vertex (key)
    * and the edge weight (value). */
   vector<map<int, int> > adjList;

   /** Constructor.
    * @pre The graph is empty.
    * @post The graph is initialized to hold n vertices. */
   Graph(int n);

   /** Determines the number of vertices in the graph.
    * @pre None.
    * @post None.
    * @return The number of vertices in the graph. */
   int getNumVertices() const;

   /** Determines the number of edges in the graph.
    * @pre None.
    * @post None.
    * @return The number of edges in the graph. */
   int getNumEdges() const;

   /** Determines the weight of an edge.
    * @pre The edge exists in the graph.
    * @post None.
    * @return The weight of the edge parameter. */
   int getWeight(Edge e) const;

   /** Creates an edge in the graph.
    * @pre The vertices exist in the graph.
    * @post Adds to both v and w's list. */
   void add(Edge e);

   /** Removes an edge from the graph.
    * @pre The vertices exist in the graph.
    * @post Removes edges from both v and w's list. */
   void remove(Edge e);

   /** Finds the edge connecting v and w.
    * @pre The edge exists.
    * @post None.
    * @return An iterator to map key w in vector[v]. */
   map<int, int>::iterator findEdge(int v, int w);

}; // end Graph
// End of header file

Graph::Graph(int n)
{
   map<int, int> element;
   adjList.assign(n, element);
   numVertices = n;
   numEdges = 0;
} // end constructor

int Graph::getNumVertices() const
{
   return numVertices;
} // end getNumVertices

int Graph::getNumEdges() const
{
   return numEdges;
} // end getNumEdges

int Graph::getWeight(Edge e) const
{
   return e.weight;
} // end getWeight

void Graph::add(Edge e)
{
   int v = e.v,
       w = e.w,
       weight = e.weight;

   adjList[v].insert(make_pair(w, weight));
   adjList[w].insert(make_pair(v, weight));
   numEdges++;
} // end add

void Graph::remove(Edge e)
{
   int v = e.v,
       w = e.w,
       weight = e.weight;

   adjList[e.v].erase(w);
   adjList[e.w].erase(v);
   numEdges--;
} // end remove

map<int, int>::iterator Graph::findEdge(int v, int w)
{
   map<int, int> m = adjList[v];
   map<int, int>::iterator iter = m.find(w);

   return iter;
} // end findEdge