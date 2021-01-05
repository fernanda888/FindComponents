//-----------------------------------------------------------------------------
// Maria Fernanda Becerra
// mfbecerr
// CSE101
// pa4
// Graph.c
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"
#define NIL -1
#define INF -3
#define UNDEF -2
int time=0;
//Graph Obj type
typedef struct GraphObj{
  List* V;//lists of vertex and neighbors 
  char* c;//colors used for BFS
  int* p;//parents of index in BFS
  int* d;//distance from vertex to source in BFS
  int* disc;//discover times
  int* fin;//finish times
  int order;//number of vertices
  int size;//number of edges
  int source;//last number called by BFS
}GraphObj;
/*** Constructors-Destructors ***/

// newGraph() returns a Graph pointing to a newly created GraphObj 
// representing a graph having n vertices and no edges.
Graph newGraph(int n){
  Graph G= malloc(sizeof(GraphObj));
  G->V=calloc((n+1),sizeof(List));
  for(int i=1;i<=n;i++){
    G->V[i]=newList();
  }
  G->c=calloc((n+1),sizeof(char));
  for(int i=1;i<=n;i++){
    G->c[i]='w';
  }
  G->p=calloc((n+1),sizeof(int));
  for(int i=1;i<=n;i++){
    G->p[i]=NIL;
  }
  G->d=calloc((n+1),sizeof(int));
  for(int i=1;i<=n;i++){
    G->d[i]=INF;
  }
  G->disc=calloc((n+1),sizeof(int));
  for(int i=1;i<=n;i++){
    G->disc[i]=UNDEF;
  }
  G->fin=calloc((n+1),sizeof(int));
  for(int i=1;i<=n;i++){
    G->fin[i]=UNDEF;
  }
  G->order=n;
  G->size=0;
  G->source=NIL;

  return G;
}

// freeGraph() frees all dynamic memory associated with the Graph
// *pG, then sets the handle *pG to NULL. 
void freeGraph(Graph* pG){
  if(pG!=NULL && *pG!=NULL){
    makeNull(*pG);
    free((*pG)->V);
    free((*pG)->c);
    free((*pG)->p);
    free((*pG)->d);
    free((*pG)->disc);
    free((*pG)->fin);
    free(*pG);
    *pG=NULL;
  }
}

/*** Access functions ***/

// getOrder() returns order of Graph G
int getOrder(Graph G){
  if(G==NULL){
    printf("Graph Error: calling getOrder() on NULL Graph reference\n");
    exit(1);
  }
  return G->order;
}

// getSize() returns size of Graph G;
int getSize(Graph G){
  if(G==NULL){
    printf("Graph Error: calling getSize() on NULL Graph reference\n");
    exit(1);
  }
  return G->size;
}

// getSource() returns the source vertex most recently used in function BFS(),
// or NIL if BFS() has not yet been called. 
int getSource(Graph G){
  if(G==NULL){
    printf("Graph Error: calling getSource() on NULL Graph reference\n");
    exit(1);
  }
  return G->source;
}

//  getParent() will return the parent of vertex u in the BreadthFirst tree created by BFS()
// or NIL if BFS() has not yet been called. 
// Pre: 1<= u <=getOrder(G)
int getParent(Graph G, int u){
  if(G==NULL){
    printf("Graph Error: calling getParent() on NULL Graph reference\n");
    exit(1);
  }
  if(1>u || u>getOrder(G)){
    printf("Graph Error: calling getParent() on non-existing vertex reference\n");
    exit(1);
  }
  return G->p[u];
}

// getDist() returns thedistance from the most recent BFS source to vertex u, 
// or INF if BFS() has not yet been called. 
// Pre: 1<= u <=getOrder(G)
int getDist(Graph G, int u){
  if(G==NULL){
    printf("Graph Error: calling getDist() on NULL Graph reference\n");
    exit(1);
  }
  if(1>u || u>getOrder(G)){
    printf("Graph Error: calling getDist() on non-existing vertex reference\n");
    exit(1);
  }
  return G->d[u];
}

// getPath() appends to the List L the vertices of a shortest path in G from source to u, 
// or appends to L the value NIL if no such path exists.
// Pre:  getSource(G)!=NIL
// Pre: 1<= u <=getOrder(G)
void getPath(List L, Graph G, int u){
  if(G==NULL){
    printf("Graph Error: calling getPat() on NULL Graph reference\n");
    exit(1);
  }
  if(1>u || u>getOrder(G)){
    printf("Graph Error: calling getPath() on non-existing vertex reference\n");
    exit(1);
  }
  if(getSource(G)==NIL){
    printf("Graph Error: calling getPath() on non-existing source reference\n");
    exit(1);
  }
  if(u==getSource(G)){
    append(L,getSource(G));
  }
  else if(getParent(G,u)==NIL){
    append(L,NIL);
  }
  else{
    getPath(L,G,getParent(G,u));
    append(L,u);
  }
}
//getDiscover() returns the dicovered time of the vertex u of graph G
//Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u){
  if(G==NULL){
    printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
    exit(1);
  }
  if(1>u || u>getOrder(G)){
    printf("Graph Error: calling getDiscover() on non-existing vertex reference\n");
    exit(1);
  }
  return G->disc[u];
}
//getFinish() returns the finish time of the vertex u of Graph G
//Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u){
  if(G==NULL){
    printf("Graph Error: calling getFinish() on NULL Graph reference\n");
    exit(1);
  }
  if(1>u || u>getOrder(G)){
    printf("Graph Error: calling getFinish() on non-existing vertex reference\n");
    exit(1);
  }
  return G->fin[u];
}
/*** Manipulation procedures ***/
void Visit(Graph G, int x){
  time++;
  G->disc[x]=time;
  G->c[x]='g';
  for(moveFront(G->V[x]);index(G->V[x])>-1;moveNext(G->V[x])){
    int y=get(G->V[x]);
    if(G->c[y]=='w'){
      G->p[y]=x;
      Visit(G,y);
    }
  }
  G->c[x]='b';
  time++;
  G->fin[x]=time;
}

//makeNull() deletes all edges of G, restoring it to its original(no edge) state
void makeNull(Graph G){
  if(G==NULL){
    printf("Graph Error: calling makeNull() on NULL Graph reference\n");
    exit(1);
  }
  for(int i=1;i<=getOrder(G);i++){
    freeList(&(G->V[i]));
  }
}

//addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, 
//and v to the adjacency List of u
// Pre: 1<= u <=getOrder(G)
void addEdge(Graph G, int u, int v){
  if(G==NULL){
    printf("Graph Error: calling addEdge() on NULL Graph reference\n");
    exit(1);
  }
  if(1>u || u>getOrder(G)){
    printf("Graph Error: calling getPath() on non-existing vertex reference\n");
    exit(1);
  }
  if(1>v || v>getOrder(G)){
    printf("Graph Error: calling getPath() on non-existing vertex reference\n");
    exit(1);
  }
  if(length(G->V[u])==0){
    append(G->V[u],v);
  }
  else{
    moveFront(G->V[u]);
    while(index(G->V[u])>-1 && get(G->V[u])<v){
      moveNext(G->V[u]);
    }
    if(index(G->V[u])<0){
     append(G->V[u],v);
    }
    else{
      insertBefore(G->V[u],v);
    }
  }
  if(length(G->V[v])==0){
    append(G->V[v],u);
  }
  else{
    moveFront(G->V[v]);
    while(index(G->V[v])>-1 && get(G->V[v])<u){
      moveNext(G->V[v]);
    }
    if(index(G->V[v])<0){
      append(G->V[v],u);
    }
    else{
      insertBefore(G->V[v],u);
    }
  }
  G->size++;
}

//addArc() inserts a new directed edge from u to v, i.e. v is added to the adjacency List
// of u (but not u to the adjacency List of v).
// Pre: 1<= u <=getOrder(G)
void addArc(Graph G, int u, int v){
  if(G==NULL){
    printf("Graph Error: calling addEdge() on NULL Graph reference\n");
    exit(1);
  }
  if(1>u || u>getOrder(G)){
    printf("Graph Error: calling getPath() on non-existing vertex reference\n");
    exit(1);
  }
  if(1>v || v>getOrder(G)){
    printf("Graph Error: calling getPath() on non-existing vertex reference\n");
    exit(1);
  }
  if(length(G->V[u])==0){
    append(G->V[u],v);
  }
  else{
    moveFront(G->V[u]);
    while(index(G->V[u])>-1 && get(G->V[u])<v){
      moveNext(G->V[u]);
    }
    if(index(G->V[u])<0){
      append(G->V[u],v);
    }
    else{
      insertBefore(G->V[u],v);
    }
  }
  G->size++;
}

//BFS() runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent,
//and source fields of G accordingly
void BFS(Graph G, int s){
  if(G==NULL){
    printf("Graph Error: calling addEdge() on NULL Graph reference\n");
    exit(1);
  }
  if(1>s || s>getOrder(G)){
    printf("Graph Error: calling getPath() on non-existing vertex reference\n");
    exit(1);
  }
  G->source=s;
  for(int i=1;i<=getOrder(G);i++){
    if(i==s){
      G->c[i]='g';
      G->d[i]=0;
      G->p[i]=NIL;
    }
    else{
      G->c[i]='w';
      G->d[i]=INF;
      G->p[i]=NIL;
    }
  }
  List Q=newList();
  append(Q,s);
  moveFront(Q);
  while(index(Q)>-1){
    int x=get(Q);
    for(moveFront(G->V[x]);index(G->V[x])>-1;moveNext(G->V[x])){
      int y=get(G->V[x]);
      if(G->c[y]=='w'){
        G->c[y]='g';
        G->d[y]=(G->d[x])+1;
        G->p[y]=x;
        append(Q,y);
      }
    }
    G->c[x]='b';
    moveNext(Q);
  }
  freeList(&Q);
}

//DFS() performs a depth first search algorithm on Graph G
//Pre: length(S)==getOrder(G)
void DFS(Graph G, List S){
  if(G==NULL){
    printf("Graph Error: calling DFS() on NULL Graph reference\n");
    exit(1);
  }
  if(getOrder(G)!=length(S)){
    printf("Graph Error: calling DFS() on invalid List reference\n");
    exit(1);
  }
  for(int i=1;i<=getOrder(G);i++){
    G->c[i]='w';
    G->p[i]=NIL;
  }
  time=0;
  for(moveFront(S);index(S)>-1;moveNext(S)){
    int x=get(S);
    if(G->c[x]=='w'){
      Visit(G,x);
    }
  }
  clear(S);
  prepend(S,1);
  for(int i=2;i<=getOrder(G);i++){
    moveFront(S);
    while(index(S)>-1 && ((G->fin[get(S)])>(G->fin[i]))){
      moveNext(S);
    }
    if(index(S)==-1){
      append(S,i);
    }
    else{
      insertBefore(S,i);
    }
  }
}

/*** Other operations ***/

//printGraph() prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G){
if(G==NULL){
 printf("Graph Error: calling printGraph() on NULL Graph reference\n");
 exit(1);  
}
  for(int i=1;i<=getOrder(G);i++){
    fprintf(out,"%d: ",i);
    if(G->V[i]!=NULL){
      printList(out,G->V[i]);
    }
    fprintf(out,"%c",'\n');
  }
}
//transpose() returns a reference to a new Graph object representing the transpose of G
Graph transpose(Graph G){
 if(G==NULL){
   printf("Graph Error: calling printGraph() on NULL Graph reference\n");
   exit(1);  
 }
 Graph T=newGraph(getOrder(G));
 for(int i=1;i<=getOrder(G);i++){
   moveFront(G->V[i]);
   while(index(G->V[i])>-1){
     addArc(T,get(G->V[i]),i);
     moveNext(G->V[i]);
   }
 }
 return T;
}
//copyGraph() returns a refernce to a new Graph object that is a copy of G
Graph copyGraph(Graph G){
  if(G==NULL){
   printf("Graph Error: calling printGraph() on NULL Graph reference\n");
   exit(1);  
 }
 Graph C=newGraph(getOrder(G));
 for(int i=1;i<=getOrder(G);i++){
   moveFront(G->V[i]);
   while(index(G->V[i])>-1){
     addArc(C,i,get(G->V[i]));
     moveNext(G->V[i]);
   }
 }
 return C;
}
