#pragma once
#include <vector>
#define apcel_RAND_MIN -1000
#define apcel_RAND_MAX 1000


template<typename __Type>
class MyVector: public std::vector<__Type> {
  private:
    void sortBubble();    //Сортировка пузырьком      +
    void sortInsertion(); //Сортировка подстановками  +
    void sortCount();     //Сортиовка подсчётом       +
    int findBinary();    //Бинарный поиск             +
    int findInterpolation();//Интерполяционный поиск  +

    __Type countMin;
    __Type countMax;
    __Type temp;
    void sortCountMinMax();

    int random(int a, int b);
    __Type key;
  public:
    void fillWithRandomNumbers(int n);
    unsigned long int nswap; // количество перестановок элементов
    unsigned long int nview; // Количество просмотренных элементов

    enum SortType {// Тип сортировки
        Bubble,
        Insertion,
        Count
      };
    enum FindType {
        Binary,
        Interpolation
      };

    void sort(SortType type); // Сортирока указанным методом
    int find(FindType type, __Type keyIn);
};

template<typename __Type>
std::ostream &operator << (std::ostream &output, const MyVector<__Type> &v);//вывод вектора