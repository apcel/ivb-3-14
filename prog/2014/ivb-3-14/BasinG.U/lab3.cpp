/*
Variant 4
George Basin
*/

#pragma warning(disable : 4996)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

bool IsNumber(char c)
{
	return !(c<'0'||c>'9');
}

int GetNumberCount(char * str)
{
	int i = 0;
	for (int n = 0; n < strlen(str); n++)
	{
		if(IsNumber(str[n]))
			i++;
	}
	return i;
}

int CopyNumber(char * in, char * to, int offest)
{
	for (int i = 0; i < strlen(in); i++)
	{
		if(IsNumber(in[i]))
		{
			to[offest] = in[i];
			offest++;
		}
	}
	return offest;
}

int main(int argc, char **argv)
{
	setlocale(0, "Russian");
	char * str1 = strdup("Test phrase 78");
	char * str2 = strdup("simple text 595");

	int nCount = GetNumberCount(str1)+GetNumberCount(str2);
	char * result = new char[nCount];

	result[CopyNumber(str2, result, CopyNumber(str1, result, 0))] = 0;
	
	printf("Строки:\n%s\n%s\n", str1, str2);
	printf("Результат:\n%s\n", result);

	delete str1, str2, result;
	return EXIT_SUCCESS;
}
