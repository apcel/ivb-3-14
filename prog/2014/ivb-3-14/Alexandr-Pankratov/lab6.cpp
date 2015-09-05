#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::string;

struct MyStruct
{
	static int memory_count;
	int d,f,g;

	void* operator new(size_t size)
	{
		memory_count += size;
		return malloc(size);
	}
		
	void operator delete(void *p)
	{
		free(p);
	}
};

int MyStruct::memory_count = 0;
std::vector<MyStruct*> base;

void
clear()
{
	for (auto x = base.begin(); x < base.end(); x++)
		delete *x;
	base.clear();
	MyStruct::memory_count = 0;
}

void
load(string patch)
{
	clear();

	ifstream fs = ifstream(patch.c_str());

	int h=0;
	fs >> h;
	for (int i = 0; i < h; i++) {
		MyStruct* dfg = new MyStruct();
		fs>>dfg->d;
		fs>>dfg->f;
		fs>>dfg->g;
		base.push_back(dfg);
	}
	fs.close();

	printf("Файл '%s' загружен, выделено %i байт\n", patch.c_str(), MyStruct::memory_count);
}

void
save(string patch)
{
	ofstream fs(patch.c_str());

	fs<<base.size();
	fs << '\n';

	for(auto x = base.begin(); x < base.end(); x++) {
		fs << (*x)->d << ' ' << (*x)->f << ' ' << (*x)->g << '\n';
	}

	fs.close();
}

void
print()
{
	for (auto x = base.begin(); x < base.end(); x++) {
		cout << (*x)->d << ' ' << (*x)->f << ' ' << (*x)->g << '\n';
	}
	cout<<'\n';
}

void
swap(MyStruct * s, MyStruct * a)
{
	MyStruct b;
	b = *s;
	*s = *a;
	*a = b;
}

void
sort()
{
	for (int i = 0; i < base.size()-1; i++) {
		for (int j = 0; j < base.size()-1-i; j++) {
			if(base[j]->d > base[j+1]->d) {
				swap(base[j], base[j+1]);
			}
		}
	}
}

void
find(int d)
{
	for (auto x = base.begin(); x < base.end(); x++) {
		if((*x)->d == d) {
			cout << (*x)->d << ' ' << (*x)->f << ' ' << (*x)->g << '\n';
		}
	}
}

int
main()
{
	setlocale(0, "Russian");

	load("base.txt");
	print();
	sort();
	print();
	save("base2.txt");

	clear();
	system("pause");
	return EXIT_SUCCESS;
}
