//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa3
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"


/*** Struct ***///----------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct GraphObj{
    
    List *adj;
    int* color;
    int* parent;
    
    int* discover;
    int* finish;

    int ordervertices;
    int sizeedges;

} GraphObj;



// Constructors-Destructors-------------------------------------------------------------------------------------------------------------------------------------------
Graph newGraph(int n){
    if( n < 1 ){
        printf("Graph Error: calling newGraph() on vertices < 1 graph reference\n");
        exit(EXIT_FAILURE);
    }

    Graph G = malloc(sizeof(GraphObj));

    if(G != NULL){
        G->ordervertices = n;
        G->sizeedges = 0;

        G->adj = malloc((n+1) * sizeof(List));

        G->color = malloc((n+1) * sizeof(int*));
        G->parent = malloc((n+1) * sizeof(int*));
        G->discover = malloc((n+1) * sizeof(int*));
        G->finish = malloc((n+1) * sizeof(int*));

        for(int i = 1; i <= n; i++){
            G->adj[i] = newList();
            G->color[i] = WHITE;
            G->parent[i] = NIL;
            G->discover[i] = UNDEF;
            G->finish[i] = UNDEF;
        }
    }

    return G;
}
void freeGraph(Graph* pG){
    int n, i;

    if (pG != NULL && *pG != NULL){
        n = (*pG)->ordervertices;

        for (i = 1; i <= n; i++){
            freeList(&((*pG)->adj[i]));
        }

        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->discover);
        free((*pG)->finish);
        free((*pG)->adj);
        free(*pG);
        *pG = NULL;
    }
}





// Access functions---------------------------------------------------------------------------------------------------------------------------------------------------
int getOrder(Graph G){
    if( G==NULL ){
        printf("Graph Error: calling getOrder() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    return G->ordervertices;
}
int getSize(Graph G){
    if( G==NULL ){
        printf("Graph Error: calling getSize() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    return G->sizeedges;
}

int getParent(Graph G, int u){    /* Pre: 1<=u<=n=getOrder(G) */
    if( G==NULL ){
        printf("Graph Error: calling getParent() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    if( 1 > u || u > getOrder(G)){
        printf("Graph Error: calling getParent() precondition for u\n");
        exit(EXIT_FAILURE);
    }

    //--------------------------------------------------------------------------------------------------ADDED THIS IF STATEMENT
    if(getFinish(G, u) == NIL){
        return NIL;
    }

    return G->parent[u];
} 
int getDiscover(Graph G, int u){  /* Pre: 1<=u<=n=getOrder(G) */
    if( 1 > u || u > getOrder(G)){
        printf("Graph Error: calling getDiscover() precondition for u\n");
        exit(EXIT_FAILURE);
    }

    return G->discover[u];
}
int getFinish(Graph G, int u){    /* Pre: 1<=u<=n=getOrder(G) */
    if( 1 > u || u > getOrder(G)){
        printf("Graph Error: calling getFinish() precondition for u\n");
        exit(EXIT_FAILURE);
    }

    return G->finish[u];
}





// Manipulation procedures--------------------------------------------------------------------------------------------------------------------------------------------
void addArc(Graph G, int u, int v){    /* Pre: 1<=u<=n, 1<=v<=n */
    if( G==NULL ){
        printf("Graph Error: calling addArc() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    if(1 > u || u > getOrder(G)){
        printf("Graph Error: calling addArc() precondition for u\n");
        exit(EXIT_FAILURE);
    }

    if(1 > v || v > getOrder(G)){
        printf("Graph Error: calling addArc() precondition for v\n");
        exit(EXIT_FAILURE);
    }

    List A = G->adj[u];

    moveFront(A);
    if(length(A) == 0){
        append(A, v);
    }else{
        moveFront(A);
        while(get(A) < v){
            moveNext(A);
            if(index(A) == -1){
                break;
            }
        }
        if(index(A) == -1){
            append(A, v);
        }else if(get(A) == v){
            return;            
        }else{
            insertBefore(A, v);
        }
    }
    G->sizeedges++;
} 
void addEdge(Graph G, int u, int v){   /* Pre: 1<=u<=n, 1<=v<=n */
    if( G==NULL ){
        printf("Graph Error: calling addEdge() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    
    if(1 > u || u > getOrder(G)){
        printf("Graph Error: calling addEdge() precondition for u\n");
        exit(EXIT_FAILURE);
    }

    if(1 > v || v > getOrder(G)){
        printf("Graph Error: calling addEdge() precondition for v\n");
        exit(EXIT_FAILURE);
    }

    List A = G->adj[u];
    List B = G->adj[v];

    moveFront(A);
    if(length(A) == 0){
        append(A, v);
    }else{
        moveFront(A);
        while(get(A) < v){
            moveNext(A);
            if(index(A) == -1){
                break;
            }
        }
        if(index(A) == -1){
            append(A, v);
        }else if(get(A) == v){
            return;
        }else{
            insertBefore(A, v);
        }
    }

    moveFront(B);
    if(length(B) == 0){
        append(B, u);
    }else{
        moveFront(B);
        while(get(B) < u){
            moveNext(B);
            if(index(B) == -1){
                break;
            }
        }
        if(index(B) == -1){
            append(B, u);
        }else if(get(B) == v){
            return;
        }else{
            insertBefore(B, u);
        }
    }
    G->sizeedges++;
} 

// Function makeNull() deletes all edges of G, restoring it to its original (no edge) state. 
void makeNull(Graph G){

    if( G==NULL ){
        printf("Graph Error: calling makeNull() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i <= getOrder(G); i++){
        G->parent[i] = NIL;
        // G->distance[i] = INF;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
        G->color[i] = WHITE;
        clear(G->adj[i]);

    }

    G->sizeedges = 0;
    G->ordervertices = 0;
    // G->source = NIL;
}



// Visit()
// helper function for DFS()
void Visit(Graph G, List S, int x, int *time){
    if( G==NULL ){
        printf("Graph Error: calling Visit() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    List A = G->adj[x];
    G->discover[x] = ++ (*time); // discover 𝑥
    G->color[x] = GRAY;
    

    for(moveFront(A); index(A)>= 0; moveNext(A)){
        int y = get(A);
        if(G->color[y] == WHITE){
            G->parent[y] = x;
            Visit(G, S, y, time);
        }
    }
    G->color[x] = BLACK;
    G->finish[x] = ++ (*time); // finish x
    prepend(S, x);

    
}





void DFS(Graph G, List S){             /* Pre: length(S)==getOrder(G) */
    if( G==NULL ){
        printf("Graph Error: calling DFS() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    
    if(length(S) != getOrder(G)){
        printf("Graph Error: calling DFS(), pre not met\n");
        exit(EXIT_FAILURE);
    }

    int time = 0;
    for(int x = 1; x <= (G->ordervertices); x++){
        G->color[x] = WHITE;
        G->parent[x] = NIL;
        G->discover[x] = UNDEF;
        G->finish[x] = UNDEF;
    }

    for(moveFront(S); index(S) >= 0; moveNext(S)){
        int x = get(S);
        if(G->color[x] == WHITE){
            Visit(G, S, x, &time);
        }
    }

    for(moveFront(S); index(S) >= 0; moveNext(S)){
        deleteBack(S);
    }

}





// Other Functions----------------------------------------------------------------------------------------------------------------------------------------------------
Graph transpose(Graph G){
    if( G==NULL ){
        printf("Graph Error: calling transpose() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    Graph transposegraph = newGraph(getOrder(G));

    for(int i = 1; i <= G->ordervertices; i++){
        moveFront(G->adj[i]);
        while(index(G->adj[i]) != -1){
            int x = get(G->adj[i]);
            addArc(transposegraph, x, i);
            moveNext(G->adj[i]);
        }
    }    

    return transposegraph;
}
Graph copyGraph(Graph G){
    if( G==NULL ){
        printf("Graph Error: calling copyGraph() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    Graph copygraph = newGraph(getOrder(G));

    for(int i = 1; i <= G->ordervertices; i++){
        moveFront(G->adj[i]);
        while(index(G->adj[i]) != -1){
            addArc(copygraph, i, get(G->adj[i]));
            moveNext(G->adj[i]);
        }
    }    

    return copygraph;

}
void printGraph(FILE* out , Graph G){
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling printGraph() on NULL graph reference.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 1; i <= G->ordervertices; i++){
        moveFront(G->adj[i]);
        fprintf(out, "%d: ",i );
        while(index(G->adj[i]) > -1){
            fprintf(out, "%d ", get(G->adj[i]));
            moveNext(G->adj[i]);
        }
        fprintf(out, "\n");
    }
}


