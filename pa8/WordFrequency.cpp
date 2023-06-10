//-----------------------------------------------------------------------------
//Preston Nguyen
//prhunguy
//pa8
//-----------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include<string>
#include <cctype>

#include"Dictionary.h"


using namespace std;

int main(int argc, char * argv[]){

    Dictionary D;

    ifstream in;
    ofstream out;

    string line;

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

    int lineCount = 0;
    
    while(getline(in, line)){
        lineCount++;
        size_t begin = 0;
        size_t end = 0;
        size_t len = line.length();

        while(end < len){

            begin = line.find_first_not_of(delim, end);
            // If no more words on the line
            if(begin == string::npos){
                break;
            }


            end = line.find_first_of(delim, begin);
            // Last word on the line
            if(end == string::npos){
                end = len; 
            }


            string token = line.substr(begin, end - begin);

            // Lowercase words
            for(size_t i = 0; i < token.length(); i++){
                token[i] = tolower(token[i]);
            }

            // Update the word frequency in the dictionary
            if(D.contains(token)){
                int& freq = D.getValue(token);
                freq++;
            }else{
                D.setValue(token, 1);
            }
        }
    }

    // Print dictionary
    out << D << endl;

    

    // close files
    in.close();
    out.close();

    return 0;
}





    