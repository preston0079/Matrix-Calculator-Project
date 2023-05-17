//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa5
//-----------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include<string>
#include"List.h"

#include <cstdlib>

using namespace std;

void shuffle(List& D);

int main(int argc, char * argv[]){

    // check command line for correct number of arguments
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <deck size>" << std::endl;
        return(EXIT_FAILURE);
    }
    

    //get user unput for size of deck
    int decksize = stoi(argv[1]);

    //if deck size is negative
    if (decksize <= 0) {
        std::cerr << "Usage: " << argv[0] << " invalid deck size" << std::endl;
        return(EXIT_FAILURE);
    }


    std::cout << "deck size       shuffle count" << std::endl;
    std::cout << "------------------------------" << std::endl;


    List deck, original;
    int count;

    for (int i = 1; i <= decksize; i++) {

        //insert into deck
        deck.moveBack();
		deck.insertBefore(i);

        original = deck;

        //start shuffle
        shuffle(deck);
        count = 1;

        //repeat shuffle until equal
        while (!deck.equals(original)){
            shuffle(deck);
            count++;
        }

        //print contents of table
        if(i <= 9){
			std::cout << " "<< i << "               "<< count <<std::endl;
		}else if(i <= 99){
			std::cout << " "<< i << "              "<< count <<std::endl;
		}else{
            std::cout << " "<< i << "             "<< count <<std::endl;
        }
    }
    
    return(EXIT_SUCCESS);
}

void shuffle(List& D){
    int length = D.length();
    int half = length / 2;

    List A, B;
    B = D;

    B.moveFront();

    //split deck
    for (int i = 0; i < half; i++) {
        A.insertBefore(B.front());
        B.eraseAfter();
    }

    D.clear();

    A.moveFront();
    B.moveFront();

    //alternate with insert back into D
    for (int i = 0; i < half; i++) {
        D.insertBefore(B.moveNext());
        D.insertBefore(A.moveNext());
    }

    // if odd length
    if (length % 2 == 1) {
        D.insertBefore(B.moveNext());
    }
    
}

