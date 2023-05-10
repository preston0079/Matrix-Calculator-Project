//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa2
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Graph.h"
#include "List.h"


int main(int argc, char *argv[]){

    FILE *input_file;
    FILE *output_file;

    // n = #vertices; u, v = vertex of two edges
    int n, u, v;
    Graph G;

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
        addEdge(G, u, v);
    }

    printGraph(output_file, G);

    List pathfindings = newList();

    while(1){
        fscanf(input_file, " %d", &u);
        fscanf(input_file, " %d", &v);

        if(u == 0 ||  v == 0){
            break;
        }

        BFS(G, u);
        getPath(pathfindings, G, v);
        
        if(length(pathfindings) == 0 || getDist(G, v) < 0){
            fprintf(output_file, "\nThe distance from %d to %d is infinity\n", u, v);
            fprintf(output_file, "No %d-%d path exists\n", u, v);
        }else{
            fprintf(output_file, "\nThe distance from %d to %d is %d\n", u, v, getDist(G, v));
            fprintf(output_file, "A shortest %d-%d path is: ", u, v);

            printList(output_file, pathfindings);
        }

        clear(pathfindings);
    }

    freeGraph(&G);
    freeList(&pathfindings);


    fclose(input_file);
    fclose(output_file);

    return 0;

}




