//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa4
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "Matrix.h"
#include "List.h"

typedef struct EntryObj *Entry;

// private Entry Object type
typedef struct EntryObj {
    int col;
    double val;
} EntryObj;

typedef struct MatrixObj {
    int size;
    int NNZ;
    List *row;
} MatrixObj;

// constructor for entry
Entry newEntry(int column, double value) {
    
    // column can't be less than 0
    if(column < 0){
        printf("Error: newEntry() column less than 0\n");
        exit(EXIT_FAILURE);
    }

    Entry E = malloc(sizeof(EntryObj));
    E->col = column;
    E->val = value;

    return E;
}

void deleteEntry(Entry *pE) {
    
    if( pE!=NULL && *pE!=NULL ){
        free(*pE);
        *pE = NULL;
    }

}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
    
    if(n < 0){
        printf("Error: newMatrix n less than 0\n");
        exit(EXIT_FAILURE);
    }

    Matrix M = malloc(sizeof(MatrixObj));

    M->size = n;
    M->NNZ = 0;

    M->row = malloc((n+1) * sizeof(List));

    for(int i = 1; i <= n; i++){
        M->row[i] = newList();
    }

    return M;

}


// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    
    if (pM != NULL && *pM != NULL){

        makeZero(*pM);
        free(*pM);
        *pM = NULL;
    }

}





// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
    if( M == NULL ){
        printf("Error: calling size() on NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    
    return M->size;
}


// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    if( M == NULL ){
        printf("Error: calling size() on NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }

    return M->NNZ;
}


// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){

    if( A==NULL || B==NULL ){
        printf("Error: calling equals() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }    

    Entry x, y;
    List c, d;

    if(A->size != B->size){
        return 0;
    }


    // for(int i = 1; i <= A->size; i++){

    //     c = A->row[i];
    //     d = B->row[i];
    //     moveFront(c);
    //     moveFront(d);

    //     if(length(A->row[i]) == length(B->row[i])){
    //         // while the indexes of the lists[i] are GTE 0 && their sizes are equal:
    //         while( (index(c) >= 0 && index(d) >= 0) && (A->size == B->size) ){
    //             x = (Entry)get(A->row[i]);
    //             y = (Entry)get(B->row[i]);

    //             if(x->val != y->val){
    //                 return 0;
    //             }
    //             if(x->col != y->col){
    //                 return 0;
    //             }
    //             moveNext(A->row[i]);
    //             moveNext(B->row[i]);
    //         }
    //     }else{
    //         return 0;
    //     }
    // }
    // return 1;
    
    for(int i = 1; i <= A->size; i++){

        c = A->row[i];
        d = B->row[i];
        moveFront(c);
        moveFront(d);

        if(length(A->row[i]) == length(B->row[i])){
            continue;
        }else{
            return 0;
        }

        while( (index(c) >= 0 && index(d) >= 0) && (A->size == B->size)){
            x = (Entry)get(A->row[i]);
            y = (Entry)get(B->row[i]);

            if(x->val != y->val){
                return 0;
            }
            if(x->col != y->col){
                return 0;
            }
            moveNext(A->row[i]);
            moveNext(B->row[i]);
        }
    }
    return 1;


    // similar to List implementation of equals
    // check if lengths of the metrics are equal and exit if they are not
    // Entry x, y;
    // List c, d;
    // int i;
    
    // from "i" = 1 to size of "A":
    //      set "c" and "d" to the rows of "A" and "B"
    //      move to the front of both lists
    //      while the indexes of the lists[i] are GTE 0 && their sizes are equal:
                // x = (Entry)get(A->row[i]);
                // y = (Entry)get(B->row[i]);
    //          if their values are not equal return false
    //          else move next on "c" and "d"
    // return 1;
}


// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
    if(M == NULL){
        printf("Error: calling makeZero() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    M->NNZ = 0;

    for(int i = 1; i <= M->size; i++){
        for(moveFront(M->row[i]); index(M->row[i]) >= 0; moveNext(M->row[i])){
            Entry E = (Entry)get(M->row[i]);
            deleteEntry(&E);
        }
        clear(M->row[i]);
    }

    // set NNZ to 0
    // iterate through the matrix:
    //      for each row in the matrix:
    //          free the entries and move next on the rows
    //      clear each row
}


// changeEntry()---------------------------------------------------------------------------------------------------------------------------------------------
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    
    if(M == NULL){
        printf("Error: calling changeEntry() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    
    if( (1 > i  &&  i > size(M)) || (1 > j && j > size(M))){
        printf("Error: calling changeEntry() on invalid Matrix reference (precondition error)\n");
        exit(EXIT_FAILURE);
    }

    List L = M->row[i];
    Entry E = NULL;

    // for(moveFront(L); get(L) == j; moveNext(L)){
    //     break;
    // }

    // if(L == NULL || index(L) == -1){
    //     if(x != 0){
    //         E = newEntry(j, x);
    //         append(L, E);
    //     }
    //     M->NNZ++;
    // }else if(M->row[i] > j){
    //     if(x != 0){
    //         E = newEntry(j, x);
    //         insertBefore(L, E);
    //     }
    //     M->NNZ++;
    // }else{
    //     if(x != 0){
    //         E->val = x;
    //     }else{
    //         freeList(&L);
    //         M->NNZ--;
    //     }
    // }

    if((length(L) == 0) && x != 0){
        E = newEntry(j, x);
        append(L, E);
        M->NNZ++;
    }else{
        for(moveFront(L); index(L) >= 0; moveNext(L)){
            E = (Entry)get(L);
            if(E->col == j){
                if(x != 0){
                    E = (Entry)get(L);
                    E->val = x;
                }else{
                    E = (Entry)get(L);
                    deleteEntry(&E);
                    delete(L);
                    M->NNZ--;
                }
                break;
            }else if(E->col > j){
                if(x != 0){
                    E = newEntry(j, x);
                    insertBefore(L, E);
                    M->NNZ++;
                }
                break;
            }
        }
        if(index(L) == -1){
            if(x != 0){
                E = newEntry(j, x);
                append(L, E);
                M->NNZ++;
            }   
        }
    }


    // Set the entry to null and assign List L to the row at index i
    //       iterate through the L until you reach column j, then break
    //       if L was empty of the index fell off the back of L
    //               append the new value x to L if x is not 0 (add to end of row)
    //               increment the NNZ
    //       else if still on L but past column j--------------------------------------------------------------------------------------------------------------
    //               insert the new value x before the current index if x is not 0
    //               increment the NNZ
    //       else (still on L at column j)
    //               if x is not 0, set the entry value to x
    //               else delete L and decrement the NNZ
}


// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){

    if(A == NULL){
        printf("Error: calling copy() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix copy = newMatrix(size(A));
    Entry E;
    int i, col;
    double val;

    for(i = 1; i <= A->size; i++){
        moveFront(A->row[i]);
        while(index(A->row[i]) >= 0){
            E = get(A->row[i]);
            col = E->col;
            val = E->val;

            Entry F = newEntry(col, val);
            append(copy->row[i], F);

            copy->NNZ++;

            moveNext(A->row[i]);
        }
    }
    return copy;
    
    // iterate "i" from 1 to size of matrix "A" (inclusive):
    //      move to the front of the matrix A's rows at index "i"
    //      iterate through the rows[i] as long as the index is GTE 0:
    //          assign Entry E to the cursor's data
    //          set col to the E's column
    //          set val to the E's value
    //          append a new entry of (col, val) to matrix Copy's row at index "i"
    //          increment the nnz value of copy and move to the next index of rows in A
}


// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){

    if(A == NULL){
        printf("Error: calling transpose() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix T = newMatrix(size(A));
    Entry E;
    int i, col;
    double val;

    T->NNZ = A->NNZ;
    for(i = 1; i <= A->size; i++){
        moveFront(A->row[i]);
        while(index(A->row[i]) >= 0){
            E = get(A->row[i]);
            col = E->col;
            val = E->val;

            Entry F = newEntry(i, val);
            append(T->row[col], F);

            moveNext(A->row[i]);

        }
    }
    return T;

    // similar to Copy() but use "i" as the column now

    // set the Transpose matrix T's nnz to be the same as A
    // iterate "i" from 1 to size of matrix "A" (inclusive):
    //      move to the front of the matrix A's rows at index "i"
    //      iterate through the rows[i] as long as the index is GTE 0:
    //          assign Entry E to the cursor's data
    //          set col to the E's column
    //          set val to the E's value
    //          append a new entry of (i, val) to matrix T's row at index "i"
    //          increment the nnz value of copy and move to the next index of rows in A
}


// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    
    if(A == NULL){
        printf("Error: calling scalarMult() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }     

    Matrix M = newMatrix(size(A)); 
    Entry E;
    int i, col;
    double val;

    // if x is 0 or A's nnz is 0 just return M
    if(x == 0 || A->NNZ == 0){
        return M;
    }

    M->NNZ = A->NNZ;

    for(i = 1; i <= A->size; i++){
        moveFront(A->row[i]);
        while(index(A->row[i]) >= 0){
            E = get(A->row[i]);
            
            col = E->col;
            
            val = E->val * x;

            Entry F = newEntry(col, val);

            append(M->row[i], F);

            moveNext(A->row[i]);

        }

    }

   

    return M;

    // set the matrix M's nnz to be the same as A
    // iterate "i" from 1 to size of matrix "A" (inclusive):
    //      move to the front of the matrix A's rows at index "i"
    //      iterate through the rows[i] as long as the index is GTE 0:
    //          assign Entry E to the cursor's data
    //          set col to the E's column
    //          set val to the E's value * x
    //          append a new entry of (i, val) to matrix Copy's row at index "i"
    //          increment the nnz value of copy and move to the next index of rows in A

}



// helper function vector sum for functions sum() diff()
// Assuming C is an empty List object, sets C to P+Q (if flag==1) or P-Q 
// (if flag==-1), considered as sparse vectors. 
// Pre: P!=Q, P and Q are rows in different Matrix objects.--------------------------------------------------------------------------------
void vecSum(List A, List B, List C, int sign, Matrix M) {
    double x, y, z;
    Entry a, b;

    // Read this before moving on:
    // int "x" can nonly be 1 or -1, indicating if the computation
    // is going to be a subtraction or addition
    // to add/sub two vals it will work like this: val1 + (x)val2
    // if x is 1 it will add normally, if its negative one, it will subtract it
    // **&&** === this symbol is for the line i am reffering to

    // if(sign <= 1){
    //     moveFront(A);
    //     moveFront(B);
    // }
    moveFront(A);
    moveFront(B);

    while(index(A) >= 0 && index(B) >= 0){
        a = get(A);
        b = get(B);
        x = a->val;
        y = (sign) * b->val;
        if(a->col == b->col){
            z = x + y;
            if(z != 0){
                Entry E = newEntry(a->col, z);
                append(C, E);
                M->NNZ++;

            }
            moveNext(A);
            moveNext(B);
        }else if(a->col < b->col){
            Entry F = newEntry(a->col, x);
            append(C, F);
            M->NNZ++;
            moveNext(A);
            
        }else{
            Entry G = newEntry(b->col, y);
            append(C, G);
            M->NNZ++;
            moveNext(B);
        }
    }

    while(index(A) >= 0){
        a = get(A);
        Entry H = newEntry(a->col, (a->val));
        append(C, H);
        M->NNZ++;
        moveNext(A);
    }


    while(index(B) >= 0){
        b = get(B);
        Entry I = newEntry(b->col, (sign)*(b->val));
        append(C, I);
        M->NNZ++;
        moveNext(B);
    }


    // move to the front of both lists
    // iterate through the two lists as long as their indexes are GTE 0:
        // assign Entry "a" and "b" to the cursor's data at list "A" and "B"
        // set x to the value of entry "a"
        // **&&** set y to (sign)*value of entry "b"
        // if the column of entry "a" equals "b's":
        //      set z to the sum of x and y
        //      if z isn't 0 then append a new entry of (a's col, z) to list C
        //      move to the next element of List A and B
        // else if Entry "a's" column is LT "b's"
        //      append a new entry of (a's col, x) to list C
        //      catch up with list A by calling moveNext on it
        // else
        //      append a new entry of (b's col, y) to list C
        //      catch up with list B by calling moveNext on it

    // iterate through your list A as long as it's index is GTE 0:
    //      assign Entry "a" to the cursor's data at list "A"
    //      append a new entry of (a's co, a's val) to List C
    //      move the cursor to the next element of list A

    // iterate through your list B as long as it's index is GTE 0:
    //      assign Entry "b" to the cursor's data at list "B"
    //      append a new entry of (b's col, b's val) to List C
    //      move the cursor to the next element of list B
}



// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    
    if(A == NULL){
        printf("Error: calling sum() on NULL Matrix A reference\n");
        exit(EXIT_FAILURE);
    }

    if(B == NULL){
        printf("Error: calling sum() on NULL Matrix B reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(A) != size(B)){
        printf("Error: calling sum() Pre failure\n");
        exit(EXIT_FAILURE);
    }

    Matrix Add = newMatrix(size(A));

    if(equals(A, B)){
        return scalarMult(2, A);
    }else{
        for(int i = 1; i <= Add->size; i++){
            vecSum(A->row[i], B->row[i], Add->row[i], 1, Add);
        }
    }

    // for(int i = 1; i < Add->size; i++){-----------------------------------------------------CHANGED VECSUM TO INCLUDE MATRIX, COUNTS NNZ
    //     Add->NNZ += length(Add->row[i]);
    // }

    return Add;

    // if A and B are equal just set Add by calling scalarMult on either of the matrices by 2
    // else iterate "i" from 1 to size of the matrix:
    //      set ADD's row at index "i" by calling vecSum on A's rows[i], B's rows[i]
}


// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    
    if(A == NULL){
        printf("Error: calling diff() on NULL Matrix A reference\n");
        exit(EXIT_FAILURE);
    }

    if(B == NULL){
        printf("Error: calling diff() on NULL Matrix B reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(A) != size(B)){
        printf("Error: calling diff() Pre failure\n");
        exit(EXIT_FAILURE);
    }

    Matrix Diff = newMatrix(size(A));

    if(equals(A, B)){
        makeZero(Diff);
        return Diff;
    }else{
        for(int i = 1; i <= Diff->size; i++){
            vecSum(A->row[i], B->row[i], Diff->row[i], (-1), Diff);
        }
    }

    // if(equals(A, B)){
    //     makeZero(Diff);
    //     return Diff;
    // }
    // for(int i = 1; i <= Diff->size; i++){
    //     vecSum(A->row[i], B->row[i], Diff->row[i], -1, Diff);
    // }


    // for(int i = 1; i <= Diff->size; i++){-----------------------------------------------------CHANGED VECSUM TO INCLUDE MATRIX, COUNTS NNZ
    //     Diff->NNZ += length(Diff->row[i]);
    // }

    return Diff; 

    // if A and B are equal just call make zero on Diff and return it
    // else iterate "i" from 1 to size of the matrix:
    //      set Diff's row at index "i" by calling vecSum on A's rows[i], B's rows[i]

}



// vectorDot()
// Returns the dot product of Lists P and Q considered as sparse vectors.
// Pre: P!=Q, P and Q are rows in different Matrix objects.--------------------------------------------------------------------------------
double vecDot(List A, List B) {

    if( A==NULL ){
        printf("List Error: calling vecDot() on NULL List reference A\n");
        exit(EXIT_FAILURE);
    }

    if( B==NULL ){
        printf("List Error: calling vecDot() on NULL List reference B\n");
        exit(EXIT_FAILURE);
    }

    double dp = 0.0;
    Entry a, b;

    moveFront(A);
    moveFront(B);

    while(index(A) >= 0 && index(B) >= 0){
        a = get(A);
        b = get(B);

        if(a->col == b->col){
            dp += (a->val * b->val);
            moveNext(A);
            moveNext(B);
        }else if(a->col < b->col){
            moveNext(A);
        }else{
            moveNext(B);
        }
    }
    return dp;

    // move to the front of both lists
    // iterate through the two lists as long as their indexes are GTE 0:
        // assign Entry "a" and "b" to the cursor's data at list "A" and "B"

        // if the column of entry "a" equals "b's":
        //      increment dp by the multiplicaion of entry "a" and "b's" values
        //      move to the next element of List A and B
        // else if Entry "a's" column is LT "b's"
        //      catch up with list A by calling moveNext on it
        // else catch up with list B by calling moveNext on it
}




// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    
    if(A == NULL){
        printf("Error: calling product() on NULL Matrix A reference\n");
        exit(EXIT_FAILURE);
    }

    if(B == NULL){
        printf("Error: calling product() on NULL Matrix B reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(A) != size(B)){
        printf("Error: calling product() Pre failure\n");
        exit(EXIT_FAILURE);
    }

    Matrix M = newMatrix(size(A));

    // for (int i = 1; i <= size(M); i++) {
    //     M->row[i] = newList();
    // }

    Matrix T = transpose(B);

    int i, j;
    double x;

    for(i = 1; i < A->size+1; i++){
        for(j = 1; j < A->size+1; j++){
            
            if(length(A->row[i]) == 0){
                break;
            }

            x = vecDot(A->row[i], T->row[j]);
            if(x != 0.0){
                Entry E = newEntry(j, x);
                append(M->row[i], E);
                M->NNZ++;
            }
        }
    }
    freeMatrix(&T);
    return M;


    // iterate "i" from 1 to size of Matrix A:-------------------------------------------------ADD +1 TO SIZE, SAME FOR ONE BELOW
    //      iterate "j" from 1 to size of Matrix A:

    //          set "x" to the dot product of Matrix A's row[i] and T's row[j]
    //          if "x" isn't zero:
    //              append new entry (j, x) to Matrix M
    //              increment the nnz 

    // free the transpose matrix
    
}



// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    Entry E = newEntry(0, 0);
    int cont = 0;
    for (int i = 1; i <= size(M); i++) {
        cont = 0;
        moveFront((M->row[i]));
        if (index(M->row[i]) >= 0) {
            E = (Entry) get(M->row[i]);
            if (E) {
                fprintf(out, "%d: ", i);
                cont = 1;
            }
        }
        while (index((M->row[i])) >= 0) {
            E = (Entry) get(M->row[i]);
            if (E) {
                fprintf(out, "(%d, %.1f) ", E->col, E->val);
            }
            moveNext(M->row[i]);
        }
        if (cont == 1) {
            fprintf(out, "\n");
        }
    }
}

