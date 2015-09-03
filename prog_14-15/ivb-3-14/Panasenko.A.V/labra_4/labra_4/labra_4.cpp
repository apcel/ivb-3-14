#include <iostream>
#include <fstream>
#include <string>
/*
* Лабораторная работа №4
* ИВБ-3-14
* Панасенко Андрей
* 16 вариант
	Для какого-нибудь числа n (n<=1000) посчитать сумму всех чисел на, которые n делится без остатка.
	В строке входного файла INPUT.TXT записанно натуральное число n (n<=1000)
	В выходной файл OUTPUT.TXT выведите сумму всех натуральных всех натуральных делителей числа n.
*/
using namespace std;
void 
keep_window_open() {
	char q;
	cin >> q;
}

int
main(int argc, char **argv)
{
	setlocale(0, "Russian");
	std::ifstream In = std::ifstream("INPUT.txt");

	if (!In.is_open())
	{
		printf_s("Нет файла :(\n");
		return -1;
	}

	int n;
	In >> n;
	In.close();
	printf_s("n:%d\n", n);
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		if (n%i == 0)
		{
			sum += i;
		}
	}
	printf_s("Сумма делителей равна:%d\n\n", sum);
	std::ofstream Out = std::ofstream("OUTPUT.txt");
	Out << sum;
	Out.close();
	keep_window_open();
	return EXIT_SUCCESS;
}
