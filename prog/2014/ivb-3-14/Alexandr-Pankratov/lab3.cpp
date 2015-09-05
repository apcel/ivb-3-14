// 17 вариант
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

int main(int argc, char **argv)
{
	setlocale(0, "Russian");
	char * input = strdup("Текст /*от лат. textus — ткань; сплетение, связь, сочетание*/ — зафиксированная на каком-либо материальном носителе человеческая мысль; в общем плане связная и полная последовательность символов.");

	printf("Исходная строка:\n%s\n", input);

	int pos = 0;
	int len = strlen(input);
	char * output = new char[len];

	bool flag = false;
	for (int i = 0;i < len - 1; i++)
	{
		if(flag){
			if(input[i]=='*'&&input[i+1]=='/'){
				flag = false;
				i++;
			}
		}else
		{
			if(input[i]=='/'&&input[i+1]=='*'){
				flag = true;
				i++;
			}
			else
			{
				output[pos] = input[i];
				pos++;
			}
		}
	}

	if(!flag){
		output[pos] = input[len-1];
		pos++;
	}
	output[pos] = 0;

	printf("Результат:\n%s\n", output);
	
	delete input;
	delete output;
	return EXIT_SUCCESS;
}
