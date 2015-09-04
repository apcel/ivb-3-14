// this is task ¹1, my variant - the even
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <clocale>

using namespace std;

template <typename Type>
class MyVector : public std::vector<Type>
{
public:
	MyVector(vector <Type> str) : std::vector<Type>(str){}

	~MyVector()
	{
		cout << endl << " Object to destroyed!!!";
	}

	void print() // output to the screen
	{
		int i = 0;
		auto it = begin();
		while (it != end())
		{
			if (i > 0)
				cout << " ";
			cout << *it;
			++it;
			++i;
		}
		cout << endl;
	}

	void rand_fill() // vector fills randomly numbers
	{
		srand(time(0));
		for (auto it = begin(); it != end(); it++)
		{
			*it = rand() % 100000;
		}
		cout << endl;
	}

	void sort_shell() // method by Shell
	{

		int e = 0; // numbers obmenov
		int comp = 0; // numbers sravneniy
		int step = size() / 2;
		while (step > 0)
		{
			++comp;
			for (int i = 0; i < (size() - step); i++)
			{
				int j = i;
				while (j >= 0 && at(j) > at(j + step))
				{
					++comp;
					++comp;
					int temp = at(j);
					at(j) = at(j + step); 
					at(j + step) = temp;
					j--;
					++e;
					++e;
				}
			}
			step = step / 2;
		}
		cout << "Method by Shell e = " << e << " comp = " << comp;
	}
	void sort_merge(int first, int last, static int &e, static int &comp) // method merger
	{
		e++;
		if (first < last)
		{
			sort_merge(first, (first + last) / 2, e, comp); //  sorting left side
			sort_merge((first + last) / 2 + 1, last, e, comp); //sorting the right side 
			merge(first, last, e, comp); // swap parts
		}
	}
	void merge(int first, int last, static int &e, static int &comp)
	{
		int middle, start, final, j;
		vector<Type> mas;
		middle = (first + last) / 2; 
		start = first; 
		final = middle + 1; 
		for (j = first; j <= last; j++) {
			if ((start <= middle) && ((final > last) || (at(start) < at(final))))
			{
				++comp;
				++comp;
				++comp;
				mas.push_back(at(start));
				start++;
			}
			else
			{
				++comp;
				++comp;
				++comp;
				mas.push_back(at(final));
				final++;
			}
		}
		// return result
		for (j = first; j <= last; j++)
		{
			at(j) = mas[j - first];
		}
	}

	void swap_my(iterator begin, iterator min, static int &e1, static int &comp1) // swap
	{
		Type temp = *begin;
		*begin =*min;
		*min = temp;
		++e1;
		++e1;
		++e1;
	}

	void sort_case(static int &e1, static int &comp1) // method case
	{
		for (auto it = begin(); it != end(); it++)
		{ 
			swap_my(it, min(it, e1, comp1), e1, comp1);
		}
	}

	iterator min(iterator it, static int &e1, static int &comp1) // finds the minimum number of vector
	{

		iterator min = it;
		for (; it != end(); it++)
		{
			if (*it < *min) {
				min = it;
				++comp1;
			}
		}
		return min;
	}

	int find_direct(int number) //returns the index of number // direct find
	{
		int index = 0;
		for (auto it = begin(); it != end(); it++, index++)
		{
			if (*it == number)
				return index;
		}
		return -1;
	}

	int number_fib(const int n)// calculate the number of fibbonachi
	{
		unsigned long long f1, f2;
		if ((n == 0) || (n == 1)) {
			return n;
		} else if (n >= 2) {
			f1 = number_fib(n - 1);
			f2 = number_fib(n - 2);
			return f1 + f2;
		}
	}

	int find_fibonachi(const int n, const int key)// find by Fibbonachi
	{
		int t, search, mid, i, c;
		int f1, f2;
		int j = 1;
		while (number_fib(j) < (n + 1))
		{
			j = j + 1;
		}
		mid = n - number_fib(j - 2) + 1;
		f1 = number_fib(j - 2);
		f2 = number_fib(j - 3);
		c = 0;
		for (;;)
		{
			if (c == 1)
				break;
			if (mid > 0)
				if (key == at(mid))
					break;
			if ((mid <= 0) || (key > at(mid)))
			{
				if (f1 == 1)
				{
					c = 1;
				}
				else
				{
					mid = mid + f2;
					f1 = f1 - f2;
					f2 = f2 - f1;
				}
			}
			else
			{
				if (f2 == 0)
				{
					c = 1;
				}
				else
				{
					mid = mid - f2;
					t = f1 - f2;
					f1 = f2;
					f2 = t;
				}
			}
		}
		if (c) 
			search = 0;
		else 
			search = mid;
		if ((!search) || (search == n)) {
			cout << ("number is not found  ");
			return -1;
		}
		else
			return search;
	} 
};