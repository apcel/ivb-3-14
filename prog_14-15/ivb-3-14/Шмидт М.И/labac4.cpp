#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

int igra(int data[], int left, int rigth, int player, int scope1, int scope2){
	if (left<=rigth){
		int il = igra(data,left+1,rigth,3-player,scope2,scope1+data[left]);
		int ir = igra(data,left,rigth-1,3-player,scope2,scope1+data[rigth]);
		if (il==player || ir==player)
			return player;
		else if (il==0 || ir==0)
			return 0;
		else 
			return 3-player;
	} else
		if (scope1>scope2)
			return player;
		else if (scope1<scope2)
			return 3-player;
		else 
			return 0;
}

int main(){
	ifstream fin;
	fin.open("INPUT.TXT");
	int n;
	fin>>n;
	int data[99];
	for(int i = 0; i<n; i++)
		fin>>data[i];
	fin.close();
	
	ofstream fout;
	fout.open("OUTPUT.TXT");
	fout<<igra(data,0,n-1,1,0,0);
	fout.close();
	return EXIT_SUCCESS;
}
