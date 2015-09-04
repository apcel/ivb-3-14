/*
Variant 4
George Basin
*/

#pragma warning(disable: 4996)
#include <iostream>
#include <fstream>
#include <string>

void WriteToStream(std::ofstream * stream, int * buffer, int length)
{
	for (int i = 0; i < length; i++)
	{
		*stream << buffer[i];
		if (i + 1 != length)
			*stream << ' ';
	}
	*stream << '\n';
}

int main(int argc, char **argv)
{
	setlocale(0, "Russian");
	std::ifstream In = std::ifstream("input.txt");

	int N, pCount = 0, nCount = 0, pOffest = 0, nOffest = 0;
	In >> N;

	int * data = new int[N];
	for (int i = 0; i < N; i++)
	{
		In >> data[i];
		if (data[i] % 2 == 0)
			pCount++;
		else
			nCount++;
	}

	In.close();

	int * p = new int[pCount];
	int * n = new int[nCount];

	for (int i = 0; i < N; i++)
	{
		if (data[i] % 2 == 0)
			p[pOffest++] = data[i];
		else
			n[nOffest++] = data[i];
	}

	std::ofstream Out = std::ofstream("output.txt");

	WriteToStream(&Out, n, nCount);
	WriteToStream(&Out, p, pCount);

	if (pCount >= nCount)
		Out << "YES";
	else
		Out << "NO";

	Out.close();

	delete data, n, p;
	return 0;
}
