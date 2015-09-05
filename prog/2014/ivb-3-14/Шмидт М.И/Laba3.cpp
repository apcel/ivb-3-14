#include <stdlib.h>
#include <stdio.h>
#include <iostream>

/*
	Написать программу получения строки, в которой удалены все «лишние» пробелы,
	то есть из нескольких подряд идущих пробелов оставить только один.
*/

int
main()
{
	char * input = _strdup("vdhjkdq dwqdqwd     qwdq d  qwd   dwq wd q dqwd qyh  yh  ggh");
	std::cout << input << std::endl;

	int len = strlen(input);
	char * result = new char[len];

	int n = 0;
	for (int i = 0; input[i]; i++, n++) {
		if (input[i] == ' ') {
	            i++;
		    result[n++] = ' ';
                    while (input[i] == ' ')
	                i++;
		}
		result[n] = input[i]; 
	}
	result[n] = 0;

	std::cout << result << std::endl;
	system("pause");

	delete result;
	free(input);

	return EXIT_SUCCESS;
}
