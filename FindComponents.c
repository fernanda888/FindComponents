//-----------------------------------------------------------------------------
// Maria Fernanda Becerra
// mfbecerr
// CSE101
// pa4
// FindComponents.c
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"
#define INF -3
#define NIL -1
#define UNDEF -2

int main(int argc, char * argv[]){
   FILE *in, *out;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
    out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   int n=0;
   fscanf(in,"%d",&n);
   Graph G=newGraph(n);
   int x=-1;
   int y=-1;
   fscanf(in,"%d",&x);
   fscanf(in,"%d",&y);
   while(x!=0 && y!=0){
      addArc(G,x,y);
      fscanf(in,"%d",&x);
      fscanf(in,"%d",&y);
   }
   fprintf(out,"%s","Adjacency list representation of G:\n");
   printGraph(out,G);
   fprintf(out,"%s","\n");
   Graph T=transpose(G);
   List S=newList();
   for(int i=1;i<=n;i++){
     append(S,i);
   }
   DFS(G,S);
   DFS(T,S);
   int scc=0;
   for(int i=1;i<=n;i++){
     if(getParent(T,i)==NIL){
       scc++;
     }
   }
//printList(out,S);
   fprintf(out,"G contains %d strongly connected components:\n",scc);
   if(scc>0){
     moveBack(S);
     List P=newList();
     for(int i=1;i<=scc;i++){
       fprintf(out,"Component %d: ",i);
       while(index(S)>-1 && getParent(T,get(S))!=NIL){
        // fprintf(out,"%d ",get(S));
         prepend(P,get(S));
         movePrev(S);
       }
       if(index(S)>-1){
         prepend(P,get(S));
        // fprintf(out,"%d",get(S));
         movePrev(S);
       }
       printList(out,P);
       fprintf(out,"\n");
       clear(P);
     }
     freeList(&P);
   }
   // close files 
   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   fclose(in);
   fclose(out);
   return(0);
}
