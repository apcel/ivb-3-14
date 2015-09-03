#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

int main(int argc, char **argv)
{
    setlocale(0, "Russian");
    char * data = strdup("Test phrase");

    printf("Строка:\n%s\n", data);
    printf("Результат:");

    int n,len = strlen(data);
    for (int i = 0; i < len; i++)
    {
        if(data[i]!=' '){
            n = 0;
            for (int i2 = 0; i2 < len; i2++){
                if(data[i]==data[i2])
                    n++;
            }

            if(n==2)
                printf("%c", data[i]);
        }
    }
    printf("\n");

    free (data);
    return EXIT_SUCCESS;
}
