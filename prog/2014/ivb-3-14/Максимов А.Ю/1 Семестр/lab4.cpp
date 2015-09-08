//#pragma warning(disable: 4996)
#include <cstdio>
#include <clocale>

#include <cstdlib>
//#include <cctype>
//#include <cstring>
//#include <sstream>
//#include <iostream>
static const char * const InputFileName = "input_4.txt";
static const char * const OutputFileName = "output_4.txt";


int main (int argc, char **)
{
    FILE *fd;
    setlocale(LC_ALL, "Russian");

    fd = fopen (InputFileName, "r");
    if (fd != NULL) {
        long long int inp[3];
        
        fscanf(fd, "%lli %lli %lli", &inp[0], &inp[1], &inp[2]);
        fclose(fd);
        long long int max, min = inp[0];
        
        for (int i = 1; i <= 2; i++) {
            if (max < inp[i]) {
                max = inp[i];
            };
            if (min > inp[i]) {
                min = inp[i];
            };
        }

        FILE *fd_2;
        fd_2 = fopen(OutputFileName , "w");
        if (fd_2 != NULL) {
            long long answer = max - min;
            fprintf(fd_2, "%lli", answer);
        }
    } else {
        fprintf(stderr, "Входной файл \"%s\" не найден.\n", InputFileName);
    }
    fprintf(stdout, "Нажмите любую клавишу для продолжения...");
    fgetc(stdin);
    return EXIT_SUCCESS;
}



