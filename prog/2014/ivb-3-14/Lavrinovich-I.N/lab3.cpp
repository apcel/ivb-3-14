#include <iostream>
#include <fstream>
#include <string>

/*
    Вариант 13.
    Дана строка, состоящая из слов, разделенных пробелами. Сформировать новую
строку со следующими свойствами: все слова длины более 3 символов, содержащие только цифры, удаляются.
    
*/

bool Is3NumberOnly(char * string, int len)
{
	int n = 0;

	for (int i = 0; i < len; i++)
		if(string[i] >= '0' && string[i] <= '9')
			n++;
		else
			return false;

	return n>3;
}

int main(int argc, char **argv)
{
	char * phrase = strdup("dfjwke ew we 45 wef9 48 wewe 4448 erwer666 wed22e wd5wed5wed65d6dd 5e5e5e555 5533");
	int m = 0, p = 0, len = strlen(phrase);

	char * NewPhr = new char[len + 1];
	char * buff = new char[len];

	for (int i = 0; i <= len; i++) {
		if(phrase[i] == ' ' || i == len) {
			if(m != 0) {
				if(!Is3NumberOnly(buff, m)) {
					for (int n = 0; n < m; n++)
						NewPhr[p++] = phrase[i - n - 1];

					NewPhr[p++] = ' ';
				}
				m = 0;
			}
		} else
			buff[m++] = phrase[i];
	}
	NewPhr[p] = 0;
	printf("%s\n%s\n", phrase, NewPhr);
	free(phrase);
	delete[] buff, NewPhr;
	return 0;
}
