//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa7
//-----------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;

int main(int argc, char * argv[]){

    Dictionary D;

    ifstream in;
    ofstream out;

    string line;
    int line_num = 1;

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
    

    // Read each line of input and place it in D
    while (getline(in, line)) {
        D.setValue(line, line_num);
        line_num++;
    }

    // Print out the dictionary to the outfile
    out << D << endl;



    // Print out the pre-order traversal of the tree to the outfile
    out << D.pre_string() << endl;


    // close files
    in.close();
    out.close();

   return 0;
}