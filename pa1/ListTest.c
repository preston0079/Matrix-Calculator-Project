//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa1
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"


int main(int argc, char* argv[]){
   

   //test newList
   List test = newList();

   for(int i=1; i<=10; i++){
      append(test,i);
   }

   //test printList
   printf("\nShould print: 1 2 3 4 5 6 7 8 9 10\n");
   printf("Mine:         ");
   printList(stdout, test);

   printf("\n");

   //test length
   printf("Length() should be: 10\n");
   printf("My length():        %d\n", length(test));

   printf("\n");

   //test front
   printf("Front() should be: 1\n");
   printf("My front():        %d\n", front(test));

   printf("\n");

   //test back
   printf("Back() should be: 10\n");
   printf("My back():        %d\n", back(test));

   printf("\n");

   //test prepend
   prepend(test, 88);
   printf("Prepend() 88 should look like: 88 1 2 3 4 5 6 7 8 9 10\n");
   printf("Mine:                          ");
   printList(stdout, test);

   printf("\n");

   //test append
   append(test, 66);
   printf("Append() 66 should look like: 88 1 2 3 4 5 6 7 8 9 10 66\n");
   printf("Mine:                         ");
   printList(stdout, test);

   printf("\n");

   //test get()
   printf("Index and value for last element in list should be:\nIndex: 11\nValue: 66\n");
   moveBack(test);
   printf("index(): %d\n", index(test));
   printf("get():   %d\n", get(test));

   printf("\n");

   //test deletefront and deleteback
   printf("List should be back to original state 1-10 after deleteFront() and deleteBack()\n");
   printf("Original: ");
   printList(stdout, test);
   printf("Result:      ");
   deleteFront(test);
   deleteBack(test);
   printList(stdout, test);

   printf("\n");

   //test moveBack(), moveFront, delete
   printf("Using moveBack() and moveFront(), delete 1 and 10 with the cursor\n");
   printf("Original:            ");
   printList(stdout, test);
   printf("Result after delete(): ");
   moveBack(test);
   delete(test);
   moveFront(test);
   delete(test);
   printList(stdout, test);

   printf("\n");

   //test index()
   printf("Cursor currently at: -1 (undefined due to deleting it)\n");
   printf("index(): %d\n", index(test));

   printf("\n");

   //test moveNext
   moveFront(test);
   moveNext(test);
   printf("Starting at front, moveNext() puts cursor at 3 (next element after 2)\n");
   printf("Result: %d\n", get(test));

   printf("\n");

   //test movePrev
   movePrev(test);
   printf("Now use movePrev() to put cursor at 2\n");
   printf("Result: %d\n", get(test));

   printf("\n");

   //test insertBefore and insertAfter
   printf("Insert 44 and 66 before and after the 5 in the list\n");
   printf("Original: ");
   printList(stdout, test);
   printf("Result:   ");
   moveNext(test);
   moveNext(test);
   moveNext(test);
   insertBefore(test, 44);
   insertAfter(test, 66);
   printList(stdout, test);

   printf("\n");

   //test set

   printf("Replace the 5 with a 55\n");
   printf("Original: ");
   printList(stdout, test);
   printf("Result:   ");
   set(test, 55);
   printList(stdout, test);

   printf("\n");

   //test copyList
   List clone = copyList(test);
   printf("Create another list that is a copy of the original\n");
   printf("Original:  ");
   printList(stdout, test);
   printf("The Clone: ");
   printList(stdout, clone);



   //test equals
   printf("Using equals(), are they the same? ");
   printf("%s\n", equals(test, clone)?"TRUE!":"FALSE!");

   printf("\n");

   //test if equals is false
   printf("Replace 55 from the original with 11 and see if they are still equal\n");
   moveBack(test);
   movePrev(test);
   movePrev(test);
   movePrev(test);
   movePrev(test);
   movePrev(test);
   set(test, 11);
   printf("Original:  ");
   printList(stdout, test);
   printf("The Clone: ");
   printList(stdout, clone);
   printf("Using equals(), are they the same? ");
   printf("%s\n", equals(test, clone)?"TRUE!":"FALSE!");

   printf("\n");

   //test clear
   printf("Using clear(), empty out clone\n");
   clear(clone);
   printf("Original:  ");
   printList(stdout, test);
   printf("The Clone: ");
   printList(stdout, clone);

   printf("\n");

   //test freeList
   printf("Using freeList(), get rid of clone (make NULL)\n");
   freeList(&clone);
   printf("Original:  ");
   printList(stdout, test);
   printf("The Clone: ");
   printList(stdout, clone);

   freeList(&test);

   return 0;
}


