#include <iostream>
#include <string>
/* Лабораторная работа №3
	* Вариант 16
	* ИВБ-3-14
	* Панасенко Андрей
Даны две строки s и w, вывести строку х максимальной длины, состоящую из букв,
таких, что существует перестановка х, являющаяся подстрокой перестановки s и
одновременно являющаяся подстрокой перестановки w */

void
main()
{
	char * str1 = _strdup("My string one htTp");
	char * str2 = _strdup("This simple string");
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	char * buff = new char[len2 > len1 ? len2 : len1];
	int * memory = new int[256];
	int p = 0;
	for (int i = 0; i < 256; i++)
		memory[i] = -1;
	for (int i = 0; i < len1; i++)
	{
		for (int n = 0; n < len2; n++)
		{
			if (str1[i] == str2[n])
			{
				if (!(str1[i] == ' ' && ((p > 0 && buff[p - 1] == ' ') || p == 0))) { // удаление пробелов
					if (memory[str1[i]] < n) {
						memory[str1[i]] = n;
						buff[p] = str1[i];
						p++;
						break;
					}
				}
			}
		}
	}

	buff[p] = '\0';
	printf("String 1:\t%s\nString 2:\t%s\nResult:\t\t%s\n", str1, str2, buff);
	system("pause");
	delete memory;
	delete buff;
}