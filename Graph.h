// Faisal Shaikh
// Fshaikh1
// PA5

#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#ifndef PA5_GRAPH_H
#define PA5_GRAPH_H

#define white 0
#define grey 1
#define black -1

#define NIL -2
#define INF -3
#define UNDEF -5

typedef struct Graphobj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

/*** Other operations ***/
void printGraph(FILE* out, Graph G);
void add(Graph G, List L, int x);
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void VISIT(Graph G, List S, int *time, int u);
#endif //PA5_GRAPH_H
