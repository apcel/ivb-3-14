#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
const int lines_num = 4;
const int words_num = 3;
const char* linebank[lines_num]={"Молодой человек из ", "Как-то ", "А минут через двадцать стал ", "Хоть "};
const char* wordbank[][words_num]=
        {
            {"Ростова ", "Пскова ", "Коврова "},
            {"съел на обед ", "в школу принёс ", "в стиме купил "},
            {"две подковы ", "водяного ", "домового "},
            {"ржать и ", "уныло ", "противно "},
            {"лягаться ", "болтаться ", "плеваться "},
            {"вреда не нанёс никакого ", "совсем и не думал плохого ", "потом и не помнил ни слова"}
        };
int main()
{
    setlocale( LC_ALL,"Russian" );
    int word = 0;
    for (int line = 0; line < lines_num; ++line)
    {
        std::cout << linebank[line];
        int words_in_line=1;
        if (line == 1 || line == 2) words_in_line=2;
        for (int word_in_line = 0; word_in_line<words_in_line; ++word_in_line)
        {
            int rnd_word=rand()%words_num;
            std::cout << wordbank[word][rnd_word];
            ++word;
        }
        std::cout<<std::endl;
    }
    system("pause");
    return 0;
}
