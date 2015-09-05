#include <iostream>
#include <fstream>
#include <string>

/*
	* Лаба №3
	* 15 вариант
		Непустая строка, содержащая некоторое слово, называется палиндромом, если
		это слово одинаково читается как слева направо, так и справа налево. Пусть
		дана строка, в которой записано слово s, состоящее из n прописных букв
		латинского алфавита. Вычеркиванием из этого слова некоторого набора символов
		можно получить строку, которая будет палиндромом. Требуется найти количество
		способов вычеркивания из данного слова некоторого (возможно, пустого)
		набора таких символов, что полученная в результате строка является палиндромом.
		Способы, различающиеся только порядком вычеркивания символов, считаются
		одинаковыми.
*/

bool isPal(char * sub, int offest, int len)
{
	for(int i = 0; i< len/2; i++)
		if(sub[offest+i]!=sub[offest+len-1-i])
			return false;

	return true;
}

char * GetSub(char * sub, int offest, int len)
{
	char * phrase = new char[len+1];

	for(int m=0 ; m<len; m++)
		phrase[m] = sub[offest+m];

	phrase[len] = 0;
	return phrase;
}

int main(int argc, char **argv)
{
	setlocale(0, "");

	char * phrase = strdup("testset");
	int len = strlen(phrase),
		count = 0;

	for (int i = 0; i < len; i++)
	{
		for (int n = 1; n <= len - i; n++)
		{
			if(isPal(phrase, i, n))
			{
				printf("%s\n", GetSub(phrase, i, n));
				count++;
			}
		}
	}

	printf("Существует %i различных способов получить из строки \"%s\" палиндром.\n", count, phrase);
	return 0;
}