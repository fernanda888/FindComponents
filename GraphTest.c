//-----------------------------------------------------------------------------
// Maria Fernanda Becerra
// mfbecerr
// CSE101
// pa4
// GraphTest.c
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){
Graph G= newGraph(8);
printf("%d\n",getOrder(G));
addArc(G, 1,2);
addArc(G, 1,3);
addArc(G, 1,5);
addArc(G, 2,6);
addArc(G, 2,3);
addArc(G, 2,4);
addArc(G, 3,6);
addArc(G, 3,7);
addArc(G, 3,8);
addArc(G, 4,5);
addArc(G, 4,7);
addArc(G, 5,4);
addArc(G, 6,4); 
addArc(G, 6,7);
addArc(G, 7,8);
addArc(G, 7,5);
addArc(G, 8,7);
addEdge(G, 8,4);
printf("%d\n",getSize(G));
printGraph(stdout,G);
List P=newList();
for(int i=1;i<=8;i++){
  append(P,i);
}
DFS(G,P);
printList(stdout,P);
printf("%d\n",getParent(G,3));
printf("%d\n",getDiscover(G,5));
printf("%d\n",getFinish(G,7));
Graph T=transpose(G);
Graph C=copyGraph(G);
DFS(T,P);
DFS(C,P);
printGraph(stdout,T);
printList(stdout,P);
printf("%d\n",getParent(T,3));
printf("%d\n",getDiscover(T,5));
printf("%d\n",getFinish(T,7));
printGraph(stdout,C);
printList(stdout,P);
printf("%d\n",getParent(T,3));
printf("%d\n",getDiscover(T,5));
printf("%d\n",getFinish(T,7));
printf("%d\n",getFinish(T,1));
printf("%d\n",getDiscover(G,1));
printList(stdout,P);//should be 3 1
printf("\n");
printf("%d\n",getParent(G,5));//should be 2
makeNull(G);
printGraph(stdout,G);
freeList(&P);
freeGraph(&G);
freeGraph(&C);
freeGraph(&T);
  return(0);
}
