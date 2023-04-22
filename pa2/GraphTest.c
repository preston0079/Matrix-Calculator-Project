//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa2
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){
    Graph G = newGraph(8);
    printf("Graph: \n");
    addArc(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 3, 4);

    addEdge(G, 1, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 6);
    addEdge(G, 6, 7);
    addEdge(G, 7, 8);
    addEdge(G, 8, 1);

    printGraph(stdout, G);

    List L = newList();
    BFS(G, 4);

    printf("Source: %d\n", getSource(G));
    printf("Order (vertices): %d\n", getOrder(G));
    printf("Size (edges): %d\n", getSize(G));

    printf("Parent for 3: %d\n", getParent(G, 3));
    printf("Distance for 3: %d\n", getDist(G, 8));

    getPath(L, G, 8);
    printf("Path to 8: ");
    printList(stdout, L);

    printf("Test makeNULL: ");
    makeNull(G);
    printGraph(stdout, G);

    freeGraph(&G);
    freeList(&L);


    
    return 0;
}


// void freeGraph(Graph* pG);



// void makeNull(Graph G);

