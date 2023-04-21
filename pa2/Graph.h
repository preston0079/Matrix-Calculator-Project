//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa2
//-----------------------------------------------------------------------------

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

#define WHITE -1
#define GRAY -2
#define BLACK -3

#define INF -9999
#define NIL -1000

typedef struct GraphObj* Graph;

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


/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);


/*** Other operations ***/
void printGraph(FILE* out, Graph G);


#endif

