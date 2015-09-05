
#include <string>
#include <iostream>
#include <fstream>

using std::istream;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;

class Item
{
	friend istream & operator >> (istream &f, Item &i);
	friend ostream & operator << (ostream &f, const Item &i);
public:
	int i, c, m;

	bool operator < (const Item s) {
            return c < s.c;
	}

	bool operator >(const Item s) {
            return c > s.c;
	}
};

Item * Base = nullptr;
int len = 0;

void Load_Array();
void Save_Array();
void Sort_Array();
void Print_Array();

Item* find(int index);


istream &
operator >> (istream &f, Item &i) 
{
    f >> i.i;
    f >> i.c;
    f >> i.m;
    return f;
}

ostream &
operator << (ostream &f, const Item &i)
{
    f << i.i << '\t';
    f << i.c << '\t';
    f << i.m << endl;
    return f;
}

void
Load_Array() 
{

    if (Base != nullptr) {
	delete[] Base;
	Base = nullptr;
    }
    std::ifstream f("base.txt");
    f >> len;

    Base = new Item[len];
    for (int i = 0; i < len; i++)
        f >> Base[i];

    f.close();

    int size = sizeof(Item);
    printf("Выделенно %d байт на элемент!\n", size * len, size);
}

void
Save_Array() 
{

    std::ofstream f("base.txt");
    f << len << '\n';
    for (int i = 0; i < len; i++)
        f << Base[i];

    f.close();
}

void
Sort_Array() 
{
    for (int j = 1; j <= (len - 1); j++) {
        for (int i = 0; i < len - j; i++) {
            if (Base[i] < Base[i + 1]) {
                Item m = Base[i + 1];
                Base[i + 1] = Base[i];
                Base[i] = m;
            }
        }
    }
}

void
Print_Array() 
{
    cout << "номер\tстоимость\tколличество\n";
    for (int i = 0; i < len; i++)
    cout << Base[i];
}

Item*
Find(int index) 
{
    for (int i = 0; i < len; i++)
        if (Base[i].i == index)
            return &Base[i];
    return nullptr;
}

int
main()
{
    setlocale(0, "Russian");
    Load_Array();
    cout <<("Сортировка по стоимости\n");
    Sort_Array();
    Print_Array();
    printf("Введите номер товара:");
    int n = 0;
    cin >> n;

    Item * find = Find(n);

    if (find != nullptr)
        cout << *find;
    else
        cout << "товар не найден \n";
    Save_Array();

    system("pause");
    return 0;
}



