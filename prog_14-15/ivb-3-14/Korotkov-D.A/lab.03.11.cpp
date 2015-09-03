#include <cstdio>
#include <cstdlib>
#include <string>

/*
Вариант 11
*/

int GetPhraseCount(char * buffer);
void Split(char * input, char ** &output);
char * GetPhrase(char * input, int offest, int length);
void Print(char ** buffer, int length);
bool StartWith(char * str, char * find);

char * Find = "http://";
char * Replace = "[ссылка запрещена]";

int main(int argc, char **argv)
{
	setlocale(0, "Russian");
	char * input = _strdup("Текст с ссылками. http://maps.google.com http://ya.ru/ есть большие ссылки http://eflk.ru/forum/index.php?qwery=testing");

	int phrase_count = GetPhraseCount(input);

	char ** phrases = new char *[phrase_count];

	Split(input, phrases);
	printf_s("Оригинал:\n");
	Print(phrases, phrase_count);

	int r_len = strlen(Replace) + 1;
	for (int i = 0; i < phrase_count; i++)
	{
		if (StartWith(phrases[i], Find))
		{
			delete[] phrases[i];
			phrases[i] = new char[r_len];
			strcpy(phrases[i], Replace);
		}
	}

	printf_s("\nУдаление сcылок:\n");
	Print(phrases, phrase_count);

	printf_s("\n");

	for (int i = 0; i < phrase_count; i++)
	{
		delete[] phrases[i];
	}
	delete[] phrases;
	delete input;
	return EXIT_SUCCESS;
}

bool StartWith(char * str, char * find)
{
	int l1 = strlen(str);
	int l2 = strlen(find);

	if (l2>l1)
		return false;

	for (int i = 0; i<l2; i++)
	{
		if (str[i] != find[i])
			return false;
	}

	return true;
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
		if (c == ' ')
			phrase_count++;
	} while (c != '\0');

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
		if (c == ' ')
		{
			if (h != 0){
				output[n] = GetPhrase(input, i, h);
				n++;
				h = 0;
			}
		}
		else
			h++;

	} while (c != '\0');

	output[n] = GetPhrase(input, i, h - 1);
}

char * GetPhrase(char * input, int offest, int length)
{
	char * phrase = new char[length + 1];

	int _offest = offest - length - 1;
	for (int m = 0; m<length; m++)
		phrase[m] = input[_offest + m];

	phrase[length] = '\0';
	return phrase;
}
