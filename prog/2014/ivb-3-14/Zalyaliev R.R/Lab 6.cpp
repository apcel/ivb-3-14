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

struct Structure
{
	static int memory;
	int a, b, c;

	void* operator new(size_t size)
	{
		memory += size;
		return malloc(size);
	}
	void operator delete(void *p)
	{
		free(p);
	}
};

std::vector<Structure*> source;
int Structure::memory = 0;

void
clear()
{
	for (auto x = source.begin(); x < source.end(); x++)
		delete *x;
	source.clear();
	Structure::memory = 0;
}

void
load(string patch)
{
	clear();

	ifstream fs = ifstream(patch.c_str());

	int z = 0;
	fs >> z;
	for (int i = 0; i<z; i++)
	{
		Structure* field = new Structure();
		fs>>field->a;
		fs>>field->b;
		fs>>field->c;
		source.push_back(field);
	}
	fs.close();

	printf("Файл '%s' загружен, выделено %i байт\n", patch.c_str(), Structure::memory);
}

void
save(string patch)
{
	ofstream fs(patch.c_str());

	fs<<source.size();
	fs << '\n';

	for (auto x = source.begin(); x < source.end(); x++) {
		fs <<(*x)->a << ' ' <<(*x)->b << ' ' <<(*x)->c << '\n';
	}

	fs.close();
}

void
print()
{
	for (auto x = source.begin(); x < source.end(); x++) {
		cout <<(*x)->a << ' ' <<(*x)->b << ' ' <<(*x)->c << '\n';
	}
	cout<<'\n';
}

void
swap(Structure * s, Structure * e)
{
	Structure g;
	g = *s;
	*s = *e;
	*e = g;
}

void
sort()
{
	for (int i = 0; i < source.size() - 1; i++) {
		for (int j = 0; j < source.size() - 1 - i; j++) {
			if (source[j]->a > source[j + 1]->a) {
				swap(source[j], source[j + 1]);
			}
		}
	}
}

void
find(int a)
{
	for (auto x = source.begin(); x < source.end(); x++) {
		if ((*x)->a == a) {
			cout <<(*x)->a << ' ' <<(*x)->b << ' ' <<(*x)->c << '\n';
		}
	}
}

int
main()
{
	setlocale(0, "Russian");

	load("source.txt");
	print();
	sort();
	print();
	save("source2.txt");

	clear();
	system("pause");
	return EXIT_SUCCESS;
}
