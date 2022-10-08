/** @file Edge.h */

/** @class Edge
 * An Edge class for graph implementations. */
class Edge
{
public:
   int v, w, weight;
   Edge(int firstVertex, int secondVertex, int edgeWeight)
   {
      v = firstVertex;
      w = secondVertex;
      weight = edgeWeight;
   }  // end constructor
}; // end Edge

// End of header file
