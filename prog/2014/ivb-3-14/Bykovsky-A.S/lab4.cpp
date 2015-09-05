//вариант 7
#include <fstream>
#include <iostream>
using namespace std;
int main()
{
    ifstream infile("INPUT.txt");
    ofstream outfile("OUTPUT.txt");
    int a;
    int b;
    int c;
    int d;
    int const MAX = 100;
    int i;
    bool opt;
    bool first = true;
    while(!infile.eof()) {
        opt = false;
        infile >> a >> b >> c >> d;
        first = true;
        for(i = -MAX; i <= MAX; i++)
            if((a*i*i*i + b*i*i + c*i + d) == 0) {
                if(!first)
                    outfile << ' ';
                first = false;
                outfile << i;
                opt = true;
            }
        if(opt)
            outfile << endl;
    }
}
