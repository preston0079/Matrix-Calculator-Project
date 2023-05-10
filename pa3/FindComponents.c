//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa3
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Graph.h"
#include "List.h"


int main(int argc, char *argv[]) {

    FILE *input_file;
    FILE *output_file;

    // Check command line for correct number of arguments, help recieved from example fileIO.c
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // Open the input file for reading
    input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    // Open the output file for writing
    output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        fprintf(stderr, "Cannot open output file %s for writing\n", argv[2]);
        exit(1);
    }

    int n, u, v; // n = #vertices; u, v = vertex of two edges
    Graph G, T;
    List S;




    fscanf(input_file, " %d", &n);

    G = newGraph(n);
    u = 1;
    v = 1;



    while(1){
        fscanf(input_file, " %d", &u);
        fscanf(input_file, " %d", &v);
        if(u == 0 ||  v == 0){
            break;
        }
        addArc(G, u, v);
    }

    fprintf(output_file, "Adjacency list representation of G:\n");
    printGraph(output_file, G);
    fprintf(output_file, "\n");




    T = transpose(G);

    // append each vertices of the graph to the list S (stack)
    S = newList();
    for(int i = 1; i <= n; i++){
		append(S, i);
	}



    DFS(G, S);
    DFS(T, S);



    int comp = 0;

    for(int i = 1; i<=getOrder(T); i++){    
        if(getParent(T, i) == NIL){
            comp++;
        }
    }
    fprintf(output_file, "G contains %d strongly connected components:\n", comp);



    // set a random variable "x" to the number of strong components
    int x = comp;


    // create and allocate an array of Lists (*List C)to store the strong components
    List *C;
    C = malloc(comp * sizeof(List));
    for(int i = 0; i < comp; i++){
		C[i] = newList();
	}


    for(moveFront(S); index(S) != -1; moveNext(S)){

        int data = get(S);

        if(getParent(T, data) == NIL){
            x--;
        }
        append(C[x], data);
    }

    for(int i = 0; i < comp; i++){
        fprintf(output_file, "Component %d: ", i+1);
        printList(output_file, C[i]);
        fprintf(output_file, "\n");
    }





    freeList(&S);
    for (int i = 0; i < comp; i++){
        freeList(&C[i]);
    }
    free(C);
    freeGraph(&G);
    freeGraph(&T);



    fclose(input_file);
    fclose(output_file);

    return 0;
}


