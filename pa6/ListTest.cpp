//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa6
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;


int main(){

    List A;


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


    return 0;


}