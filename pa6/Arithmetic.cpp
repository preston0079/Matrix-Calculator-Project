//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa6
//-----------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include<string>
#include "BigInteger.h"

using namespace std;


//based off of FileIO.cpp

int main(int argc, char *argv[]) {
    
    ifstream in;
    ofstream out;
    
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return (EXIT_FAILURE);
    }

    in.open(argv[1]);
    if(!in.is_open()){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if(!out.is_open()){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }


    string temp1;
    string temp2;

    //store into string
    in >> temp1;
    in >> temp2;

    //create BigInteger
    BigInteger A = BigInteger(temp1);
    BigInteger B = BigInteger(temp2);

    //extra variables
    BigInteger two = BigInteger("2");
    BigInteger three = BigInteger("3");
    BigInteger nine = BigInteger("9");
    BigInteger sixteen = BigInteger("16");

    
    // A
    out << (A) << endl;
    out << endl;
    
    // B
    out << (B) << endl;
    out << endl;
    
    // A+B
    out << (A + B) << endl;
    out << endl;
    
    // A-B
    out << (A - B) << endl;
    out << endl;
    
    // A-A
    out << (A - A) << endl;
    out << endl;
    
    // 3A-2B
    out << ((three * A) - (two * B)) << endl;
    out << endl;
    
    // A*B
    out << (A * B) << endl;
    out << endl;  
    
    // A^2
    out << (A * A) << endl;
    out << endl;
    
    // B^2
    out << (B * B) << endl;
    out << endl;
    
    // 9A^4 + 16B^5
    out << ((nine * (A * A * A * A)) + (sixteen * (B * B * B * B * B))) << endl;


    //close files
    in.close();
    out.close();

    return 0;
}


