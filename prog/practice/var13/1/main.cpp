#ifdef __GNUC__
#define sys_clear() system("clear")
#else
#define sys_clear() system("cls")
#endif

//#define DEBUG


#include <iostream> // Логично.
#include <time.h> // Измеряем занятое выполнением сортировки время
#include "MyVector.cpp" //Класс работы с вектором


int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int result=0;
    MyVector<int> v;
    char k='\013';
    while (k != 'q')
    {
        std::cout << std::endl << \
            "1) Вывод вектора на экран\n"\
            "2) Заполнение вектора с помощью датчика случайных чисел \n"\
            "3) Сортировка методом \"Пузырька\" \n"\
            "4) Сортировка методом вставок \n"\
            "5) Сортировка подсчётом \n"\
            "6) Бинарный поиск элемента вектора \n"\
            "7) Интерполяционный поиск элемента вектора \n"\
            "Введите \'q\' для выхода\n" \
            "//Enter \'q\' to exit\n" \
            << std::endl;
        std::cin >> k;
        long long start = clock();
        switch (k)
        {
            case '1':
            {    //Вывод вектора на экран
                std::cout << v << std::endl << "Размер вектора: " << v.size() << std::endl;
                break;
            }
            case '2':
            {    //Заполнение вектора с помощью датчика случайных чисел
                //v.~MyVector();
                int n;
                std::cout << "Введите размер вектора: ";
                std::cin >> n;
                v.clear();
                //MyVector<int> v;
                v.fillWithRandomNumbers(n);

                break;
            }
            case '3':
            {    //Сортировка методом "Пузырька"
                v.sort(MyVector<int>::Bubble);
                std::cout<<"Обменов: " << v.nswap << std::endl;
                break;
            }
            case '4':
            {    // Сортировка методом вставок
                v.sort(MyVector<int>::Insertion);
                std::cout<<"Обменов: " << v.nswap << std::endl;
                break;
            }
            case '5':
            {    //Сортировка подсчётом
                v.sort(MyVector<int>::Count);
                std::cout<<"Присваиваний: " << v.nswap
                    << "\nПримечание: одна операция обмена == три операции присваивания" << std::endl;
                break;
            }
            case '6':
            {    //Бинарный поиск элемента вектора

                int t;
                std::cout << "Введите искомый элемент: ";
                std::cin >> t;
                start = clock();
                //
                result = v.find(MyVector<int>::Binary, t);
                if (result < 0) {
                    std::cout << "Элемент не найден\n";
                } else {
                    std::cout << "Элемент найден: " << result+1 << "\nКоличество просмотров: " << v.nview << "\n";
                }
                break;
            }
            case '7':
            {    //Интерполяционный поиск элемента вектора
                int t;
                std::cout << "Введите искомый элемент: ";
                std::cin >> t;
                start = clock();
                result = v.find(MyVector<int>::Interpolation, t);
                if (result < 0) {
                    std::cout << "Элемент не найден\n";
                } else {
                    std::cout << "Элемент найден: " << result+1 << "\nКоличество просмотров: " << v.nview << "\n";
                }
                break;
            }
            case 'q':
            {
                return 0;
            }
            default:
            {
                std::cout << "Sorry, your input \"" << k << "\" was not recognised.\n" \
                             "Press any_key -> Enter to continue\n";
                char a;
                std::cin >> a;
                start = clock();

            }
        };
        std::cout << " time = " << clock() - start << " ms" << std::endl;
    }

    return 0;
}