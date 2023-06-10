//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa8
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

    Dictionary A;

    string S[] =   {
                    "Somebody",
                    "once",
                    "told",
                    "me",
                    "The", 
                    "world", 
                    "is", 
                    "gonna", 
                    "roll",
                    "me",
                    "I", 
                    "aint", 
                    "the", 
                    "sharpest", 
                    "tool", 
                    "in", 
                    "the", 
                    "shed"
                    };
    

    // insert into A
    for(int i=0; i<18; i++){
        A.setValue(S[i], i+1);
    }

    cout << A.pre_string() << endl;

    cout << "A.size() = " << A.size() << endl  << A << endl;

    cout << "shed value: " << A.getValue("shed") << endl;

    cout << endl;

    cout << "test remove I" << endl;

    A.remove("I");

    cout << A << endl;




    return(EXIT_SUCCESS);
}