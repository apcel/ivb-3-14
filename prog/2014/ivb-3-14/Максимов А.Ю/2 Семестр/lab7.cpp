#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>




using namespace std;

int main(int argc, char *argv[])
{

    char buffer;
    string matching;
    regex r_number("[[:digit:]]+(\\.[[:digit:]]*)?");
    regex r_literal("[a-zA-Z_]+");
    regex r_symbol("[^a-zA-Z_[:d:]]");

    //FILE * filein = fopen("/tmp/a.in", "r+");
    #define filein stdin

    buffer = fgetc(filein);
    matching.clear();
    while(!feof(filein)) {
        matching.push_back(buffer);
        if(regex_match(matching, r_number) || regex_match(matching, r_symbol) || regex_match(matching, r_literal)) {

            buffer = fgetc(filein);
        } else {
            matching.pop_back();
            if(regex_match(matching, r_number))
                //cout << "Found number: \'" << matching << "\'" << endl;
                printf("%-20s%s\n", "Found number: " , matching.c_str());

            if (regex_match(matching, r_literal))
                //cout << "Found literal: \'" << matching << "\'" << endl;
                printf("%-20s%s\n", "Found literal: " , matching.c_str());

            if (regex_match(matching, r_symbol))
                //cout << "Found symbol: \'" << matching << "\'" << endl;
                printf("%-20s%s\n", "Found symbol: " , matching.c_str());
            matching.clear();
        }
    }

    return 0;
}