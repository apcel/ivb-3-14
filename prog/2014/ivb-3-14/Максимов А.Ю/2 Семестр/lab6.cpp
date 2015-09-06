//make collection
//Maksimov A.IO.

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

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

void load();
void save();
void sort();
void print();

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
load() 
{

    if (Base != nullptr) {
	delete[] Base;
	Base = nullptr;
    }
    std::ifstream f("input.txt");
    f >> len;

    Base = new Item[len];
    for (int i = 0; i < len; i++)
        f >> Base[i];

    f.close();

    int size = sizeof(Item);
    printf("Выделенно %d байт на элемент!\n", size * len, size);
}

void
save() 
{

    std::ofstream f("input.txt");
    f << len << '\n';
    for (int i = 0; i < len; i++)
        f << Base[i];

    f.close();
}

void
sort() 
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
print() 
{
    cout << "Номер\tСтоимость\tКолличество\n";
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
    load();
    cout <<("Сортировка по стоимости\n");
    sort();
    print();
    printf("Введите номер товара:");
    int n = 0;
    cin >> n;

    Item * find = Find(n);

    if (find != nullptr)
        cout << *find;
    else
        cout << "ОШИБКА! товар не найден \n";
    save();

    system("pause");
    return 0;
}

