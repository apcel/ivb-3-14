#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

int memory_count = 0;

struct MyStruct {
	int a, b, c;

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

class base {
	std::vector<MyStruct*> data;
public:

	base(){}
	base(std::string patch)
	{
		std::ifstream fs = std::ifstream(patch.c_str());

		int h = 0;
		fs >> h;
		for (int i = 0; i < h; i++) {
			MyStruct* dfg = new MyStruct();
			fs >> dfg->a >> dfg->b >> dfg->c;
			data.push_back(dfg);
		}
		fs.close();

		printf("Файл '%s' загружен, выделено %i байт\n", patch.c_str(), memory_count);
	}

	void save(std::string patch)
	{
		std::ofstream fs(patch.c_str());

		fs << data.size() << std::endl;

		for (auto x = data.begin(); x < data.end(); x++) {
			fs << (*x)->a << ' ' << (*x)->b << ' ' << (*x)->c << std::endl;
		}

		fs.close();
	}

	void print()
	{
		for (auto x = data.begin(); x < data.end(); x++) {
			std::cout << (*x)->a << ' ' << (*x)->b << ' ' << (*x)->c << std::endl;
		}
		std::cout << '\n';
	}

	void sort()
	{
		for (int i = 0; i < data.size() - 1; i++) {
			for (int j = 0; j < data.size() - 1 - i; j++) {
				if (data[j]->a > data[j + 1]->a) {
					auto t = data[j];
					data[j] = data[j + 1];
					data[j + 1] = t;
				}
			}
		}
	}

	void find(int d)
	{
		for (auto x = data.begin(); x < data.end(); x++) {
			if ((*x)->a == d) {
				std::cout << (*x)->a << ' ' << (*x)->a << ' ' << (*x)->a << '\n';
			}
		}
	}

	~base()
	{
		for (auto x = data.begin(); x < data.end(); x++)
			delete *x;
		memory_count = 0;
	}
};

int
main()
{
	setlocale(0, "Russian");

	base table1("base.txt");
	table1.print();
	table1.sort();
	table1.print();
	table1.save("base2.txt");

	system("pause");
	return EXIT_SUCCESS;
}
