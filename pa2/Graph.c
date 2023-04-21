//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa2
//-----------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"


//the white vertices are those that are as yet undiscovered, 
//black vertices are finished, 
//and the gray vertices are discovered, but not all of their neighbors have been discovered. 

//order is number of vertices
//size is number of edges

/*** Struct ***///----------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct GraphObj{
    // An array of Lists whose ith element contains the neighbors of vertex i.
    List *adj;
    // An array of ints (or chars, or strings) whose ith element is the color (white, gray, black) of vertex i.
    int* color;
    // An array of ints whose ith element is the parent of vertex i.
    int* parent;
    // An array of ints whose ith element is the distance from the (most recent) source to vertex i
    int* distance;

    int ordervertices;
    int sizeedges;
    int source;

} GraphObj;





/*** Constructors-Destructors ***///----------------------------------------------------------------------------------------------------------------------------------
//Function newGraph() returns a Graph pointing to a newly created GraphObj representing a graph having
//n vertices and no edges.
Graph newGraph(int n){

    if( n < 1 ){
        printf("Graph Error: calling newGraph() on vertices < 1 graph reference\n");
        exit(EXIT_FAILURE);
    }

    Graph G = malloc(sizeof(GraphObj));

    if(G != NULL){
        G->ordervertices = n;
        G->sizeedges = 0;
        G->source = NIL;

        G->adj = malloc((n+1) * sizeof(List));

        G->color = malloc((n+1) * sizeof(int*));
        G->parent = malloc((n+1) * sizeof(int*));
        G->distance = malloc((n+1) * sizeof(int*));

        for(int i = 1; i <= n; i++){
            G->adj[i] = newList();
            G->color[i] = WHITE;
            G->parent[i] = NIL;
            G->distance[i] = INF;
        }
    }

    return G;
}
//Function freeGraph() frees all heap memory associated with the Graph *pG,
//then sets the handle *pG to NULL.
void freeGraph(Graph* pG){
    int n, i;

    if (pG != NULL && *pG != NULL){
        n = (*pG)->ordervertices;

        for (i = 1; i <= n; i++){
            freeList(&((*pG)->adj[i]));
        }

        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free((*pG)->adj);
        free(*pG);
        *pG = NULL;
    }
    

}


/*** Access functions ***///------------------------------------------------------------------------------------------------------------------------------------------
// return the corresponding field values (number of vertices)
int getOrder(Graph G){

    if( G==NULL ){
        printf("Graph Error: calling getOrder() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    return G->ordervertices;
}
// return the corresponding field values (number of edges)
int getSize(Graph G){

    if( G==NULL ){
        printf("Graph Error: calling getSize() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    return G->sizeedges;
}
//getSource() returns the source vertex most recently used in function BFS(), 
//or NIL if BFS() has not yet been called. 
int getSource(Graph G){

    if( G==NULL ){
        printf("Graph Error: calling getSource() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    return G->source;
}
//Function getParent() will return the parent of vertex u in the BFS tree
//created by BFS(), or NIL if BFS() has not yet been called
// Functions getParent(), getDist() and getPath() all have the
// precondition 1 ≤ 𝑢 ≤ getOrder(𝐺).
int getParent(Graph G, int u){

    if( G==NULL ){
        printf("Graph Error: calling getParent() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    if( 1 > u || u > getOrder(G)){
        printf("Graph Error: calling getParent() precondition for u\n");
        exit(EXIT_FAILURE);
    }

    if(G->source == NIL){
        return NIL;
    }

    return G->parent[u];

}
//Function getDist() returns the distance from the most recent BFS source 
//to vertex u, or INF if BFS() has not yet been called. 
// Functions getParent(), getDist() and getPath() all have the precondition 1 ≤ 𝑢 ≤ getOrder(𝐺).
int getDist(Graph G, int u){

    if( G==NULL ){
        printf("Graph Error: calling getDist() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    if( 1 > u || u > getOrder(G)){
        printf("Graph Error: calling getDist() precondition for u\n");
        exit(EXIT_FAILURE);
    }

    if(G->source < 0){
        return INF;
    }

    return G->distance[u];
}
//Function getPath() appends to the List L the vertices of a shortest path in 
//G from source to u, or appends to L the value NIL if no such path exists.

// Function getPath() appends to the List L the vertices of a shortest path in G from source to u, or appends to 
// L the value NIL if no such path exists. getPath() has the precondition getSource(G)!=NIL, so BFS() must be called
// before getPath() is called.

// Functions getParent(), getDist() and getPath() all have the precondition 1 ≤ 𝑢 ≤ getOrder(𝐺).
void getPath(List L, Graph G, int u){

    if( G==NULL ){
        printf("Graph Error: calling getPath() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    if( L==NULL ){
        printf("List Error: calling getPath() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if( 1 > u || u > getOrder(G)){
        printf("Graph Error: calling getPath() precondition for u\n");
        exit(EXIT_FAILURE);
    }

    if(u == G->source){
        append(L, u);
    }else if(G->parent[u]  == NIL){
        append(L, NIL);
    } else {
        
        getPath(L, G, getParent(G, u));
        append(L, u);
    }
}


/*** Manipulation procedures ***///-----------------------------------------------------------------------------------------------------------------------------------
// Function makeNull() deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G){

    if( G==NULL ){
        printf("Graph Error: calling makeNull() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i <= getOrder(G); i++){
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->color[i] = WHITE;
        clear(G->adj[i]);

    }

    G->sizeedges = 0;
    G->ordervertices = 0;
    G->source = NIL;
}
// Function addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
// Both addEdge() and addArc() have the precondition that their two int arguments must lie in the range 1 to getOrder(G).
void addEdge(Graph G, int u, int v){
    
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
        }else{
            insertBefore(B, u);
        }
    }
    G->sizeedges++;
}
// Function addArc() inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v).
// Both addEdge() and addArc() have the precondition that their two int arguments must lie in the range 1 to getOrder(G).
void addArc(Graph G, int u, int v){

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
        }else{
            insertBefore(A, v);
        }
    }
    G->sizeedges++;
}
// Function BFS() runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s){
    if( G==NULL ){
        printf("Graph Error: calling BFS() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    
    for(int x = 1; x <= (G->ordervertices); x++){                       //mark all white
        G->color[x] = WHITE;
        G->distance[x] = INF;
        G->parent[x] = NIL;
    }
    G->source = s;
    G->color[s] = GRAY;                                                 // discover the source s
    G->distance[s] = 0;
    G->parent[s] = NIL;

    List Q = newList();                                                 // construct a new empty queue
    append(Q, s);
    while(length(Q) != 0){
        moveFront(Q);
        int x = front(Q);
        deleteFront(Q);
        for(moveFront(G->adj[x]); index(G->adj[x])>=0; moveNext(G->adj[x])){

            int element = get(G->adj[x]);

            if(G->color[element] == WHITE){                                    // y is undiscovered
                G->color[element] = GRAY;                                    // discover y
                G->distance[element] = G->distance[x]+1;
                G->parent[element] = x;
                append(Q, element);
            }

        }     
        G->color[x] = BLACK;                                            // finish by marking black
    }
    freeList(&Q);   

}


/*** Other operations ***///------------------------------------------------------------------------------------------------------------------------------------------
// Finally, function printGraph() prints the adjacency list representation of G to the file pointed to by out. 
// The format of this representation should match the above examples, so all that is required by the client 
// is a single call to printGraph().
void printGraph(FILE* out, Graph G){
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



