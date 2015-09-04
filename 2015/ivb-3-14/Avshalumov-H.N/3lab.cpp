/*
Строка состоит из слов, разделенных одним или несколькими пробелами. Переставьте
слова по убыванию их длин.
*/
#include <iostream>
#include <fstream>
#include <string>

void Split(char * input, char ** &output);
void Print(char ** buffer, int length);
char * GetPhrase(char * input, int offest, int length);

int main(int argc, char **argv) 
{
    setlocale(0, "Russian");
    char * input = _strdup("rftyu tfghj ftgyhuioo u jkn ii 5asd asd");
    
    int i = 0;
    int phrase_count = 1;
    char c;
    do {
        c = input[i++];
        if(c == ' ')
        phrase_count++;
    } while (c != '');
    
    char ** phrases = new char *[phrase_count];
    Split(input, phrases);
    
    printf_s("Оригинал:n");
    Print(phrases, phrase_count);
    
    for (int j = 1; j <= phrase_count - 1; j++) {
        for (int i = 0; i < phrase_count - j; i++) {
            if(strlen(phrases[i]) < strlen(phrases[i + 1])) {
                char * s = phrases[i + 1];
                phrases[i + 1] = phrases[i];
                phrases[i] = s;
            }
        }
    }
    
    printf_s("nОтсортированая строка:n");
    Print(phrases, phrase_count);
    
    printf_s("n");
    
    for (int i = 0; i < phrase_count; i++)
    delete [] phrases[i];
    delete [] phrases;
    free(input);
    
    system("pause");
    return 0;
}

char * GetPhrase(char * input, int offest, int length) 
{
    char * phrase = new char[length + 1];
    
    int _offest = offest - length - 1;
    for(int m=0 ; m < length; m++)
        phrase[m] = input[_offest + m];
    
    phrase[length] = '';
    return phrase;
}

void Print(char ** buffer, int length) 
{
    for (int i = 0; i < length; i++) {
        printf_s(buffer[i]);
        printf_s(" ");
    }
    printf_s("n");
}

void Split(char * input, char ** &output) 
{
    char c;
    int i = 0;
    int n = 0;
    int h = 0;
    
    do {
        c = input[i++];
        if(c == ' ') {
            if(h != 0) {
                output[n] = GetPhrase(input, i, h);
                n++;
                h = 0;
            }
        } else {
            h++;
        }
    } while (c != '');
    
    output[n] = GetPhrase(input, i, h - 1);
}
