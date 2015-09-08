//#define DEBUG
//#pragma warning(disable: 4996)
#include <cstdio>
#include <clocale>
#include <cstdlib>
//#include <cctype>
//#include <cstring>
//#include <sstream>
//#include <iostream>
unsigned long fsize(char* file)
{
    FILE * f = fopen(file, "r");
    fseek(f, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(f);
    fclose(f);
    return len;
}
static const char * const InputFileName = "input_3.txt";
static const unsigned long InputFileSize = fsize((char *) InputFileName); //Ит воркс, по крайней мере.
FILE *fd;    //Пусть будет глобальным. Каждый раз передавать вниз дескриптор.. Брр.

//static const char * const OutputFileName = "output_3.txt";
int recurse (int curpos, short prevmode);

int main (int argc, char **)
{
    setlocale(LC_ALL, "Russian");
#ifdef DEBUG
fprintf(stdout,"%li\n",InputFileSize);
#endif
    fd = fopen ( InputFileName , "r" );
    if(fd != NULL) {

        int allresult = -1;


         allresult = recurse (SEEK_SET, 0); //начинаем погружение.

         fprintf(stdout, "%i\n", allresult);
        fclose(fd);
    } else {
        fprintf(stderr, "Входной файл \"%s\" не найден.\n", InputFileName);
    }
    fprintf(stdout, "Нажмите любую клавишу для продолжения...");
    fgetc(stdin);
    return EXIT_SUCCESS;
}

/*    prevmode используется на этой глубине, curmode будет использоваться глубже.
 *    mode устанавливается в зависимости от того, какой символ возможен
 *    0        =>    предыдущее число было 4+ (не может составлять символ с предыдущей цифрой)
 *    10        =>    предыдущее число было 1..2 (составит символ в любом случае.)
 *     1..3    =>    предыдущее число было 3 (составит символ только если текущее число <= 3)
 *    TODO: изменить логику так, чтоб сделать меньше if'ов. Возможно, стоит сделать это через максимально возможное число
 *    Принято. Даже, кажется, реализовано.
 *        
 *    Как это работает:
 *    Функция принимает текущую позицию и то, может ли текущее число в связке с предыдущим составить символ
 *    (вернее, какой должна быть текущая цифра, чтоб составить символ с предыдущей), проверяет, возможно ли это.
 *    Если возможно, составляет и идёт глубже, предупреждая следующий уровень о том, что составить символ пока не выйдет
 *    Дальше пытается понять, есть ли возможность составить символ со следующей цифрой.
 *    И передаёт результат своей умственной деятельности вглубь.
 *    когда все более глубокие уровни "всплывут", текущий уровень тоже "всплывёт".
 */

int recurse (int curpos, short prevmode)
{    
    int result=0;    //сколько вариантов у нас будет с этого уровня рекурсии. Памяти бы хватило. По крайней мере, один путь уже есть.
    fseek(fd, curpos*sizeof(char), SEEK_SET ); // А вдруг мы провалились сюда после конца рекурсии где-то далеко внизу? 
    if (curpos >= InputFileSize) {
        return result + 1;        //мы достигли дна. Всплываем!
    } else {
        int curnum=-1;    //текущее число. 
        int nexnum=-1;


        //Тут небольшая отдельная область видимости для переменной ЦЭ.
            {    //Кажется, это может не сработать. Но зачем нам по лишней переменной на каждый уровень рекурсии?
                char c = fgetc (fd);    //ты умрёшь. Надеюсь.
                curnum = atoi (&c); 
            }

        if ((prevmode - curnum) > 0) { //Может составить символ с предыдущим. См. описание в комментарии до тела функции
            result += recurse (curpos + 1, 0);     //Идём глубже. И да, мы сейчас не сможем использовать текущую цифру глубже. <-- wut
                                    //Покажете мне закодированный тремя знаками символ -- с меня чай.
                                    // m_0{2,}_ не считается, в условии не сказано обработать всё.
        }
        int curmode = 0; // Думаю, стоит объявить это как можно позже.
        if (curnum == 3) {
            curmode = 4;    //См. комментарий перед функцией, да. 
        } else {
            if ((curnum < 3 ) && ( curnum > 0 )) {
                curmode = 10;    //Там описано поведение переменной mode
            }
        }
        // Даже если это число может составить символ с предыдущим, стоит задуматься: а не стоит ли нам взять
        // текущую цифру как отдельный символ?
                                
        result += recurse (curpos + 1, curmode);
    }
    return result;
}
