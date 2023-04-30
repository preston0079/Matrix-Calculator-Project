//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa3
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"


int main(int argc, char *argv[]){

    Graph G = newGraph(8);

    printf("Graph G: \n");
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 3, 4);

    addArc(G, 1, 4);
    addArc(G, 4, 5);
    addArc(G, 5, 6);
    addArc(G, 6, 7);
    addArc(G, 7, 8);
    addArc(G, 8, 1);

    printGraph(stdout, G);

    printf("\n");

    List L = newList();
    for(int i = 1; i <= 8; i++){
        append(L, i);
    }
    // printf("List: ");
    // printList(stdout, L);

    DFS(G, L);

    // printf("Order (vertices): %d\n", getOrder(G));
    // printf("Size (edges): %d\n", getSize(G));

    // printf("Parent for 3: %d\n", getParent(G, 3));
    printf("Discover for 3: %d\n", getDiscover(G, 3));
    printf("Finish for 3: %d\n", getFinish(G, 3));

    printf("\n");

    //copyGraph
    printf("Copy of Graph G: \n");
    Graph copyG = copyGraph(G);
    printGraph(stdout, copyG);

    printf("\n");    

    //transpose
    printf("Transpose of G: \n");
    Graph transposeG = transpose(G);
    printGraph(stdout, transposeG);





    // printf("Test makeNULL: ");
    // makeNull(G);
    // printGraph(stdout, G);

    freeGraph(&G);
    freeGraph(&transposeG);
    freeGraph(&copyG);

    freeList(&L);


    
    return 0;
}
