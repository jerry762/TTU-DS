/** @file Graph.cpp
 * An adjacency list representation of an undirected,
 * weighted graph. */

#include "Graph.h"

Graph::Graph(int n)
{
   map<int, int> element;
   adjList.assign(n, element);
   numVertices = n;
   numEdges = 0;
}  // end constructor

int Graph::getNumVertices() const
{
   return numVertices;
}  // end getNumVertices

int Graph::getNumEdges() const
{
   return numEdges;
}  // end getNumEdges

int Graph::getWeight(Edge e) const
{
   return e.weight;
}  // end getWeight

void Graph::add(Edge e)
{
   int v = e.v,
       w = e.w,
       weight = e.weight;

   adjList[v].insert(make_pair(w, weight));
   adjList[w].insert(make_pair(v, weight));
   numEdges++;
}  // end add

void Graph::remove(Edge e)
{
   int v = e.v,
       w = e.w,
       weight = e.weight;

   adjList[e.v].erase(w);
   adjList[e.w].erase(v);
   numEdges--;
}  // end remove

map<int, int>::iterator Graph::findEdge(int v, int w)
{
   map<int, int> m = adjList[v];
   map<int, int>::iterator iter = m.find(w);

   return iter;
}  // end findEdge
