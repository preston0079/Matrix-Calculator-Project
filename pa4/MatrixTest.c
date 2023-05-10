//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa4
//-----------------------------------------------------------------------------

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"

int main(int argc, char* argv[]){

    Matrix A = newMatrix(20);
    Matrix B = newMatrix(20);

    Matrix C, D, E, F, G;

    changeEntry(A, 1, 1, 1.0);
    changeEntry(A, 1, 2, 4.0);
    changeEntry(A, 1, 3, 7.0);
    changeEntry(A, 2, 1, 2.0);

    changeEntry(B, 2, 2, 5.0);
    changeEntry(B, 2, 3, 8.0);
    changeEntry(B, 2, 1, 3.0);
    changeEntry(B, 3, 2, 6.0);

    printf("A: \n");
    printMatrix(stdout, A);

    printf("\n");

    printf("B: \n");
    printMatrix(stdout, B);

    printf("\n");

    printf("Copy A: \n");
    Matrix clone = copy(A);
    printMatrix(stdout, clone);

    printf("\n");

    printf("makeZero copy (should be nothing): \n");
    makeZero(clone);
    printMatrix(stdout, clone);

    printf("\n");

    C = scalarMult(2.5, B);
    printf("scalarMult(2.5, B): %d\n", NNZ(C));
    printMatrix(stdout, C);
    printf("\n");

    printf("size A: %d\n", size(A));

    printf("NNZ B: %d\n", NNZ(B));

    printf("\n");

    D = transpose(A);
    printf("transpose(A): %d\n", NNZ(D));
    printMatrix(stdout, D);
    printf("\n");

    E = sum(A, B);
    printf("sum(A, B): %d\n", NNZ(E));
    printMatrix(stdout, E);
    printf("\n");

    F = diff(A, B);
    printf("diff(A, B): %d\n", NNZ(F));
    printMatrix(stdout, F);
    printf("\n");

    G = product(A, B);
    printf("product(A, B): %d\n", NNZ(G));
    printMatrix(stdout, G);
    printf("\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&clone);

    return 0;

}