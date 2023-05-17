//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa5
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;


int main(){

    List A, B, C;

    cout << endl;


    A.insertBefore(1);
    A.insertBefore(2);
    A.insertAfter(10);
    A.insertAfter(9);
    A.insertAfter(8);
    A.insertAfter(7);
    A.insertAfter(6);
    A.insertAfter(5);
    A.insertAfter(4);
    A.insertAfter(3);

    cout << "A = " << A << endl;
    cout << "length: " << A.length() << endl;
    cout << "front: " << A.front() << endl;
    cout << "back: " << A.back() << endl;

    A.moveFront();
    cout << "moveFront cursor: " << A.position() << endl;

    A.moveBack();
    cout << "moveBack cursor: " << A.position() << endl;

    A.movePrev();
    cout << "movePrev cursor: " << A.position() << endl;

    A.moveNext();
    cout << "moveNext cursor: " << A.position() << endl;

    A.moveFront();
    A.moveNext();

    cout << "peekPrev: " << A.peekPrev() << endl;
    cout << "peekNext: " << A.peekNext() << endl;

    A.setBefore(11);
    cout << "setBefore: " << A << endl;

    A.setAfter(22);
    cout << "setAfter: " << A << endl;

    A.eraseBefore();
    cout << "eraseBefore: " << A << endl;

    A.eraseAfter();
    cout << "eraseAfter: " << A << endl;






    cout << endl;

    B.insertAfter(2);
    B.insertAfter(4);
    B.insertAfter(4);
    B.insertAfter(6);
    B.insertAfter(6);
    B.insertAfter(2);

    B.moveFront();
    B.moveNext();
    cout << "B = " << B << endl;

    cout << "findNext 2 (cursor on space 1): " << B.findNext(2) << endl;

    B.moveBack();
    B.movePrev();
    cout << "findPrev 2 (cursor on space 6): " << B.findPrev(2) << endl;

    B.cleanup();
    cout << "B after cleanup = " << B << endl;

    cout << endl;

    cout << "A and B concat = " << A.concat(B) << endl;

    cout << endl;

    C.insertBefore(3);
    C.insertBefore(4);
    C.insertBefore(5);
    C.insertBefore(6);
    C.insertBefore(7);
    C.insertBefore(8);
    C.insertBefore(9);
    C.insertBefore(10);
    cout << "C = " << C << endl;

    cout << "A = " << A << endl;

    cout << "A and C equals (1 for true, 0 for false)? " << A.equals(C) << endl;


    return 0;


}