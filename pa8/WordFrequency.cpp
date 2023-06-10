//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa8
//-----------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include<string>
#include <cctype>

#include <algorithm>


#include"Dictionary.h"


using namespace std;

int main(int argc, char * argv[]){

    Dictionary D;

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

    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

    size_t begin, end, len;

    string line;
    string token;


    int linecount = 0;
    
    while(getline(in, line)){
        linecount++;
        len = line.length();

        // get first token
        begin = min(line.find_first_not_of(delim, 0), len);
        end = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, (end - begin));

        // we have a token
        while (token != "") {

            // make lower case
            for(size_t i = 0; i < token.length(); i++){
                token[i] = tolower(token[i]);
            }


            if (D.contains(token)) {
                D.getValue(token)++;
            }
            else {
                D.setValue(token, 1);
            }

            // get next token
            begin = min(line.find_first_not_of(delim, (end + 1)), len);
            end = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, (end - begin));
        }
    }

    // Print dictionary
    out << D << endl;

    

    // close files
    in.close();
    out.close();

    return 0;
}


