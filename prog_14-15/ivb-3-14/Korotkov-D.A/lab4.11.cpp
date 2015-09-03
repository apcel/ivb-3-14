#include <iostream>
#include <fstream>
#include <string>

/*
Определить наименьшее общее кратное чисел A и B.
*/

int main(int argc, char **argv)
{
	setlocale(0, "Russian");
	std::ifstream In = std::ifstream("input.txt");

	if (!In.is_open())
	{
		printf_s("Нет файла :(\n");
		return -1;
	}

	int A;
	int B;

	while (In >> A)
		In >> B;

	In.close();

	printf_s("A:%d\tB:%d\n", A, B);

	int min = A<B ? A : B;

	for (int i = min; i != 0; i++)
	{
		if (i%A == 0 && i%B == 0)
		{
			printf_s("Наименьшее общее кратное:%d\n\n", i);
			std::ofstream Out = std::ofstream("output.txt");
			Out << i;
			Out.close();
			return EXIT_SUCCESS;
		}
	}

	printf_s("X_X\n\n");
	return EXIT_SUCCESS;
}
