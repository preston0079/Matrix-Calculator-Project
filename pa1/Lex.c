//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa1
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 300

int main(int argc, char *argv[]){

    int line_count;
    char line[MAX_LEN];
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




    // Line counter for the input file
    line_count = 0;
    while( fgets(line, MAX_LEN, input_file) != NULL)  {
        line_count++;
    }

    // Allocate memory for the string array
    char **string_array = malloc(line_count * sizeof(char *));
    if (string_array == NULL) {
        fprintf(stderr, "Cannot allocate memory for string array\n");
        exit(1);
    }



    // Reset the file position, comes from stdio.h
    rewind(input_file);



    // Read in the lines of the input file and put them in the strings_array
    int i;
    for (i = 0; i < line_count; i++) {

        if (fgets(line, MAX_LEN, input_file) == NULL) {
            fprintf(stderr, "NULL end of input file %s\n", argv[1]);
            exit(1);
        }

        // Length of line
        size_t len = strlen(line);

        // Allocate memory, add 1 to len for null terminator
        string_array[i] = malloc(len + 1);

        if (string_array[i] == NULL) {
            fprintf(stderr, "Error with allocating memory for string\n");
            exit(1);
        }

        // Copy current line
        strncpy(string_array[i], line, len);

        // NULL terminator
        string_array[i][len] = '\0';
    }


    // Close the input file
    fclose(input_file);




    // Create the List
    List L = newList();

    // Iterate through string array and insert into list alphabetically
    for (int i = 0; i < line_count; i++) {

        // Cove cursor to beginning
        moveFront(L);

        // While the list has not reached the end AND current string is greater than or equal to the string at the current cursor element, keep moving the cursor forward
        while (index(L) >= 0 && strcmp(string_array[i], string_array[get(L)]) >= 0) {
            moveNext(L);
        }

        // When the correct position to insert the current string is found, the current index is inserted before the cursor element
        if (index(L) >= 0) {
            insertBefore(L, i);
        } else {
            //Append last when at the end
            append(L, i);
        }
    }

    // Write the sorted strings array to the output file, taken and modified from pa1 pdf
    moveFront(L);
    while (index(L) >= 0) {
        int i = get(L);
        fputs(string_array[i], output_file);
        moveNext(L);
    }

    // Close the output file
    fclose(output_file);

    // Free memory allocated
    for (i = 0; i < line_count; i++) {
        free(string_array[i]);
    }

    free(string_array);

    freeList(&L);

    return 0;
}
