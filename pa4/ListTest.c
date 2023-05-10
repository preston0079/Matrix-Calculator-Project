//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa4
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"


int main(int argc, char* argv[]){
   

   //test newList
   List test = newList();

   int fortyfour = 44;
   int fiftyfive = 55;

   int X[] = {0,1,2,3,4,5,6,7,8,9,10};

   for(int i=1; i<=10; i++){
      append(test, &X[i]);
   }


   // print list of integers
   printf("List: ");
   for(moveFront(test); index(test)>=0; moveNext(test)){
      printf("%d ", *(int*)get(test));
   }
   printf("\n");

   printf("\n");

   printf("Length() should be: 10\n");
   printf("%d \n", length(test));
   printf("\n");

   printf("\n");

   printf("front() should be: 1\n");
   printf("%d \n", *(int*)front(test));

   printf("\n");

   printf("back() should be: 10\n");
   printf("%d \n", *(int*)back(test));

   printf("\n");

   printf("get() 4 in list (moveNext 3 times)\n");
   moveFront(test);
   moveNext(test);
   moveNext(test);
   moveNext(test);
   printf("%d \n", *(int*)get(test));

   printf("\n");

   printf("insertBefore() 44\n");
   insertBefore(test, &fortyfour);
   for(moveFront(test); index(test)>=0; moveNext(test)){
      printf("%d ", *(int*)get(test));
   }
   printf("\n");

   printf("\n");

   moveFront(test);
   moveNext(test);
   moveNext(test);
   moveNext(test);
   moveNext(test);
   printf("insertAfter() 55 \n");
   insertAfter(test, &fiftyfive);
   for(moveFront(test); index(test)>=0; moveNext(test)){
      printf("%d ", *(int*)get(test));
   }
   printf("\n");

   printf("\n");

   printf("delete 4 \n");
   moveFront(test);
   moveNext(test);
   moveNext(test);
   moveNext(test);
   moveNext(test);
   delete(test);
   for(moveFront(test); index(test)>=0; moveNext(test)){
      printf("%d ", *(int*)get(test));
   }
   printf("\n");

   printf("\n");

   printf("test clear \n");
   clear(test);
   for(moveFront(test); index(test)>=0; moveNext(test)){
      printf("%d ", *(int*)get(test));
   }
   
   freeList(&test);

   return 0;
}


