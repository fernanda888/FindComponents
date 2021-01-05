//-----------------------------------------------------------------------------
// Maria Fernanda Becerra
// mfbecerr
// CSE101
// PA4
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private QueueObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev=NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}
//freAllNodes() frees all Nodes in a list headed by H
void freeAllNodes(Node H){
  if(H!=NULL){
    freeAllNodes(H->next);
    freeNode(&H);
  }
}
// newQueue()
// Returns reference to new empty Queue object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = NULL;
   L->cursor=NULL;
   L->length = 0;
   L->index=-1;
   return(L);
}
int isEmpty(List L){
  //Returns true (1) if L is empty, otherwise false(0)
  if(L==NULL){
    printf("List Error: calling isEmpty() on NULL List reference\n");
    exit(1);
  }
  return (L->length==0);
}
// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.S
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while( !isEmpty(*pL) ) { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}



// Access functions -----------------------------------------------------------
int length(List L){
  //Returns the number of elements in L
  if(L==NULL){
    printf("List Error: calling length() on NULL List reference\n");
    exit(1);
  }
  return(L->length);
}
int index(List L){
  //Returns index of cursor element if defined, -1 otherwise 
  if(L==NULL){
    printf("List Error: calling index() on NULL List reference\n");
    exit(1);
  }
  return (L->index); 
  }  
int front(List L){  
  //Returns front element of L. Pre: length()>0
  if(L==NULL){
    printf("List Error: calling front() on NULL List reference\n");
    exit(1);
  }
  if(isEmpty(L)){
    printf("List Error: calling front() on an empty List\n");
    exit(1);
  }
  return (L->front->data);
}
int back(List L){   
  //Returns back element of L. Pre: length()>0
  if(L==NULL){
    printf("List Error: calling back() on NULL List reference\n");
    exit(1);
  }
  if(isEmpty(L)){
    printf("List Error: calling back() on an empty List\n");
    exit(1);
  }
  return (L->back->data);
}
int get(List L){
  //Returns cursor element of L. Pre: length()>0, index()>=0
  if(L==NULL){
    printf("List Error: calling get() on NULL List reference\n");
    exit(1);
  }
  if(isEmpty(L)){
    printf("List Error: calling get() on an empty List\n");
    exit(1);
  }
  if(index(L)<0){
    printf("List Error: calling get() on NULL List reference\n");
    exit(1);
  }
  return (L->cursor->data);
}    
int equals(List A, List B){
 // Returns true (1) iff Lists A and B are in same 
 //state, and returns false (0) otherwise.
  if(A==NULL){
    printf("List Error: calling equals() on NULL List reference\n");
    exit(1);
  }
  if(B==NULL){
    printf("List Error: calling equals() on NULL List reference\n");
    exit(1);
  }
  int eq=0;
  eq=((A->length)==(B->length));
  Node M=A->front;
  Node N=B->front;
  while(eq && M!=NULL){
    eq=((M->data)==(N->data));
    M=M->next;
    N=N->next;
  }
  return eq;
}
// Manipulation procedures ---------------------------------------------------- 
void clear(List L){
  // Resets L to its original empty state.
  if(L==NULL){
    printf("List Error: calling clear() on NULL List reference\n");
    exit(1);
  }
  freeAllNodes(L->front);
  L->front=L->back=NULL;
  L->cursor=NULL;
  L->length=0;
  L->index=-1;
}
void moveFront(List L){
  // If L is non-empty, sets cursor under the front element,
  // otherwise does nothing.
  if(L==NULL){
    printf("List Error: calling moveFront() on NULL List reference\n");
    exit(1);
  }
  if(L->length>0){
    L->cursor=L->front;
    L->index=0;
  }
} 
void moveBack(List L){
  // If L is non-empty, sets cursor under the back element,
  // otherwise does nothing.
  if(L==NULL){
    printf("List Error: calling moveBack() on NULL List reference\n");
    exit(1);
  }
  if(L->length>0){
    L->cursor=L->back;
    L->index=(L->length)-1;
  }
}  
void movePrev(List L){
  // If cursor is defined and not at front, move cursor one
  // step toward the front of L; if cursor is defined and at
  // front, cursor becomes undefined; if cursor is undefined
  // do nothing
  if(L==NULL){
    printf("List Error: calling movePrev() on NULL List reference\n");
    exit(1);
  }
  if(L->cursor!=NULL && L->cursor!=L->front){
    Node N=L->cursor;
    L->cursor=N->prev;
    L->index=index(L)-1;
  }
  else if(L->cursor==L->front){
    L->cursor=NULL;
    L->index=-1;
  }
}   
void moveNext(List L){
// If cursor is defined and not at back, move cursor one 
// step toward the back of L; if cursor is defined and at 
// back, cursor becomes undefined; if cursor is undefined 
// do nothing
  if(L==NULL){
    printf("List Error: calling moveNext() on NULL List reference\n");
    exit(1);
  }
  if(L->cursor!=NULL && L->cursor!=L->back){
    Node N= L->cursor->next;
    L->cursor=N;
    L->index=index(L)+1;
  }
else  if(L->cursor==L->back){
    L->cursor=NULL;
    L->index=-1;
  }
}  
void prepend(List L, int data){
  // Insert new element into L. If L is non-empty,
  // insertion takes place before front element.
  if(L==NULL){
    printf("List Error: calling prepend() on NULL List reference\n");
    exit(1);
  }
  Node N= newNode(data);
  if(isEmpty(L)){
    L->front=L->back=N;
  }
  else{
    Node F= L->front;
    N->next=F;
    F->prev=N;
    L->front=N;
    if(L->cursor!=NULL){
      L->index++;
    }
  }
  (L->length)++;
} 
void append(List L, int data){
// Insert new element into L. If L is non-empty, 
// insertion takes place after back element. 
  if(L==NULL){
    printf("List Error: calling apend() on NULL List reference\n");
    exit(1);
  }
  Node N= newNode(data);
  if(isEmpty(L)){
    L->front=L->back=N;
  }
  else{
    Node B=L->back;
    B->next=N;
    N->prev=B;
    L->back=N;
  }
  (L->length)++;
}
void insertBefore(List L, int data){
// Insert new element before cursor. 
// Pre: length()>0, index()>=0 
  if(L==NULL){
    printf("List Error: calling insertBefore() on NULL List reference\n");
    exit(1);
  }
  if(isEmpty(L)){
    printf("List Error: calling insertBefore() on an empty List\n");
    exit(1);
  }
  if(L->index<0){
    printf("List Error: calling insertBefore() on NULL index reference\n");
    exit(1);
  }
  Node N=newNode(data);
  if(L->cursor==L->front){
    N->next=L->front;
    L->front->prev=N;
    L->front=N;
  }
  else{
  Node P=L->cursor->prev;
  P->next=N;
  N->prev=P;
  N->next=L->cursor;
  L->cursor->prev=N;
  }
  (L->length)++;
  L->index++;
} 
void insertAfter(List L, int data){
// Insert new element after cursor. 
// Pre: length()>0, index()>=0 
  if(L==NULL){
    printf("List Error: calling insertAfter() on NULL List reference\n");
    exit(1);
  }
  if(isEmpty(L)){
    printf("List Error: calling insertAfter() on an empty List\n");
    exit(1);
  }
  if(L->index<0){
    printf("List Error: calling insertAfter() on NULL index reference\n");
    exit(1);
  }
  Node N= newNode(data);
  if(L->cursor==L->back){
    L->back->next=N;
    N->prev=L->back;
    L->back=N;
  }
  else{
  Node A= L->cursor->next;
  A->prev=N;
  N->next=A;
  N->prev=L->cursor;
  L->cursor->next=N;
  }
  (L->length)++;
} 
void deleteFront(List L){
// Delete the front element. Pre: length()>0
  if(L==NULL){
    printf("List Error: calling deleteFront() on NULL List reference\n");
    exit(1);
  }
  if(isEmpty(L)){
    printf("List Error: calling deleteFront() on an empty List\n");
    exit(1);
  }
Node D= L->front;
  if(L->length>1){
    if(L->cursor!=NULL && L->cursor !=L->front){
      L->index--;
    }
    if(L->cursor==L->front){
      L->cursor=NULL;
      L->index=-1;
    }
    L->front=D->next;
  }
  else{
    L->front=L->back=NULL;
    L->cursor=NULL;
    L->index=-1;
  }
  freeNode(&D);
  (L->length)--;
} 
void deleteBack(List L){
// Delete the back element. Pre: length()>0
if(L==NULL){
    printf("List Error: calling deleteBack() on NULL List reference\n");
    exit(1);
  }
  if(isEmpty(L)){
    printf("List Error: calling deleteBack() on an empty List\n");
    exit(1);
  }
  Node D=L->back;
  if(L->length>1){
    if(L->cursor==L->back){
      L->cursor=NULL;
      L->index=-1;
    }
    L->back=(D->prev);
  }
  else{
    L->front=L->back=NULL;
    L->cursor=NULL;
    L->index=-1;
  }
  freeNode(&D);
  (L->length)--;
} 
void delete(List L){
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
  if(L==NULL){
    printf("List Error: calling delete() on NULL List reference\n");
    exit(1);
  }
  if(isEmpty(L)){
    printf("List Error: calling delete() on an empty List\n");
    exit(1);
  }
  if(L->index<0){
    printf("List Error: calling delete() on NULL index reference\n");
    exit(1);
  }
  Node D=L->cursor;
  if(L->length==1){
    L->front=L->back=NULL;
    L->cursor=NULL;
    L->index=-1;
  }
  else{
    if(L->cursor==L->front){
      L->front=D->next;
    }
    else if(L->cursor==L->back){
      L->back=D->prev;
    }
    else{
      Node P=L->cursor->prev;
      Node N=L->cursor->next;
      P->next=N;
      N->prev=P;
    }
    L->index=-1;
    L->cursor=NULL;
  }
  freeNode(&D);
  (L->length)--;
}
void set(List L, int x){
//Overwrites cursor element with x
//Pre: length()>0, index()>=0
  if(L==NULL){
    printf("List Error: calling set() on NULL List reference\n");
    exit(1);
  }
  if(isEmpty(L)){
    printf("List Error: calling set() on an empty List\n");
    exit(1);
  }
  if(L->index<0){
    printf("List Error: calling set() on NULL index reference\n");
    exit(1);
  }
  L->cursor->data=x;
}
  
// Other operations ----------------------------------------------------------- 
void printList(FILE* out, List L){
// Prints to the file pointed to by out, a 
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
  if(L==NULL){
    printf("List Error: calling printList() on NULL List reference\n");
    exit(1);
  }
  Node N=L->front;
  while(N!=NULL){
    fprintf(out, "%d ",N->data);
    N=N->next;
  }
//  fprintf(out,"%c",'\n');
} 
List copyList(List L){
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined, 
// regardless of the state of the cursor in L. The state 
// of L is unchanged.
  List C= newList(); 
  Node N=L->front;
  while(N!=NULL){
    append(C, N->data);
    N=N->next;
  }
  return C;
}  
List concatList(List A, List B){
// Returns a new List which is the concatenation of 
// A and B. The cursor in the new List is undefined, 
// regardless of the states of the cursors in A and B. 
// The states of A and B are unchanged.
List C= copyList(A);
Node N=B->front;
while(N!=NULL){
  append(C, N->data);
  N=N->next;
}
return C;
} 
