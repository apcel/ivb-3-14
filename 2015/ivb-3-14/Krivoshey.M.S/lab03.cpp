#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
/*
* Лаба №3
* ИВБ-3-14
* Кривошея Михаил
* 12 вариант
Дана строка, состоящая из слов, разделенных пробелами.
Сформировать новую строку со следующими свойствами:
все email заменяются на ”[контакты запрещены]”
*/

//Кол-во слов
int GetPhraseCount(char * buffer);
//Разбить на пробелы
void Split(char * input, char ** &output);
//Получить слово
char * GetPhrase(char * input, int offest, int length);
//Печать строки
void Print(char ** buffer, int length);

char * Replace = "[контакты запрещены]";

int main(int argc, char **argv)
{
	setlocale(0, "Russian");
	char * input = strdup("Текст. test@gmail.com blablabla");

	int phrase_count = GetPhraseCount(input);
	char ** phrases = new char *[phrase_count];

	Split(input, phrases);
	printf_s("Оригинал:\n");

	Print(phrases, phrase_count);
	int r_len = strlen(Replace) + 1;
	for (int i = 0; i < phrase_count; i++)
	{
		for(int n = 0; n < strlen(phrases[i]); n++)
		{
			if(phrases[i][n] == '@')
			{
				delete[] phrases[i];
				phrases[i] = new char[r_len];
				strcpy(phrases[i], Replace);
				break;
			}
		}
	}

	printf_s("\nУдаление эмейлов:\n");
	Print(phrases, phrase_count);
	printf_s("\n");

	for (int i = 0; i < phrase_count; i++)
	{
		delete [] phrases[i];
	}
	delete [] phrases;
	delete input;

	system("pause");
	return EXIT_SUCCESS;
}

char * GetPhrase(char * input, int offest, int length)
{
	char * phrase = new char[length+1];
	int _offest = offest-length-1;
	for(int m=0 ; m<length; m++)
		phrase[m] = input[_offest+m];
	phrase[length] = '\0';
	return phrase;
}

void Print(char ** buffer, int length)
{
	for (int o = 0; o < length; o++)
	{
		printf_s(buffer[o]);
		printf_s(" ");
	}
	printf_s("\n");
}

int GetPhraseCount(char * buffer)
{
	int i = 0;
	int phrase_count = 1;
	char c;
	do
	{
		c = buffer[i++];
		if(c==' ')
			phrase_count++;
	} while (c!='\0');
	return phrase_count;
}

void Split(char * input, char ** &output)
{
	char c;
	int i = 0;
	int n = 0;
	int h = 0;
	do
	{
		c = input[i++];
		if(c==' ')
		{
			if(h!=0){
				output[n] = GetPhrase(input, i, h);
				n++;
				h = 0;
			}
		}
		else
			h++;
	} while (c!='\0');
	output[n] = GetPhrase(input, i, h-1);
}
