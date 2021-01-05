//-----------------------------------------------------------------------------
// Maria Fernanda Becerra
// mfbecerr
// CSE101
// pa4
// Graph.h
//-----------------------------------------------------------------------------
#include "List.h"
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#define NIL -1
#define INF -3
#define UNDEF -2

// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

// newGraph() returns a Graph pointing to a newly created GraphObj 
// representing a graph having n vertices and no edges.
Graph newGraph(int n);

// freeGraph() frees all dynamic memory associated with the Graph
// *pG, then sets the handle *pG to NULL. 
void freeGraph(Graph* pG);

/*** Access functions ***/

// getOrder() returns order of Graph G
int getOrder(Graph G);

// getSize() returns size of Graph G;
int getSize(Graph G);

// getSource() returns the source vertex most recently used in function BFS(),
// or NIL if BFS() has not yet been called. 
int getSource(Graph G);

//  getParent() will return the parent of vertex u in the BreadthFirst tree created by BFS()
// or NIL if BFS() has not yet been called. 
// Pre: 1<= u <=getOrder(G)
int getParent(Graph G, int u);

// getDist() returns the distance from the most recent BFS source to vertex u, 
// or INF if BFS() has not yet been called. 
// Pre: 1<= u <=getOrder(G)
int getDist(Graph G, int u);

// getPath() appends to the List L the vertices of a shortest path in G from source to u, 
// or appends to L the value NIL if no such path exists.
// Pre:  getSource(G)!=NIL
// Pre: 1<= u <=getOrder(G)
void getPath(List L, Graph G, int u);

//getDiscover() returns the dicovered time of the vertex u of graph G
//Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u); 

//getFinish() returns the finish time of the vertex u of Graph G
//Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u); 


/*** Manipulation procedures ***/

//makeNull() deletes all edges of G, restoring it to its original(no edge) state
void makeNull(Graph G);

//addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency List of v 
//and v to the adjacency List of u
// Pre: 1<= u <=getOrder(G)
void addEdge(Graph G, int u, int v);

//addArc() inserts a new directed edge from u to v, i.e. v is added to the adjacency List
// of u (but not u to the adjacency List of v).
// Pre: 1<= u <=getOrder(G)
void addArc(Graph G, int u, int v);

//BFS() runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent,
//and source fields of G accordingly
void BFS(Graph G, int s);

//DFS() performs a depth first search algorithm on Graph G
//Pre: length(S)==getOrder(G)
void DFS(Graph G, List S); 

/*** Other operations ***/

//printGraph() prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);

//transpose() returns a reference to a new Graph object representing the transpose of G
Graph transpose(Graph G);

//copyGraph() returns a refernce to a new Graph object that is a copy of G
Graph copyGraph(Graph G);

#endif
