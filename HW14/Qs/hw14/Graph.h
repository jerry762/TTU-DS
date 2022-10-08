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
