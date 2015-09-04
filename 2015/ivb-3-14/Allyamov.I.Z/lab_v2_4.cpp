#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::ifstream In = std::ifstream("input.txt");

	int Number, Result = 0;
	In>>Number;
	In.close();
	
	Result = Number/10;
	Result *=Result+1;
	Result *=100;
	Result +=25;

	std::ofstream Out = std::ofstream("output.txt");
	Out<<Result;
	Out.close();

	system ("pause");
	return 0;
}
