#include <iostream>
#include "interface.h"
#include <vector>
using namespace std;

int
main()
{
	vector <int> s;
	srand(time(0));
	for (long int i = 8; i > 0; i--) {
		s.push_back(rand() % 100);
	}
	s.push_back(34);
	// for merge
	static int e = 0;
	static int comp = 0;   
	static int *ex = &e;
	static int *compan = &comp;

	// for sort_case
	static int e1 = 0;
	static int comp1 = 0;

	static int *ex1 = &e1;
	static int *compan1 = &comp1;

	MyVector <int> object(s);
	cout << "1) print \n2) sort_shell \n3) sort_merge \n4) cort_case \n5) find_fibonachi \n6) find_direct \n7) rand_fill \n Enter to q for exit\n" << endl;
	char k;
	cin >> k;
	while (k != 'q')
	{
		cout << endl << "1) print \n2) sort_shell \n3) sort_merge \n4) cort_case \n5) find_fibonachi \n6) find_direct \n7) rand_fill \n Enter to q for exit\n" << endl;
		long long start = clock();
		switch (k)
		{
		case '1':
			object.print();
			break;
		case '2':
			object.sort_shell();
			break;
		case '3':
			object.sort_merge(0, object.size() - 1, *ex, *compan);
			cout << "Method merge \t e = " << e << " comp = " << comp << endl;
			break;
		case '4':
			object.sort_case(*ex1, *compan);
			cout << "Method sort_case \t e = " << e1 << " comp = " << comp1 << endl;
			break;
		case '5':
			cout << "enter to n: ";
			int n, key;
			cin >> n;
			cout << "\nenter to key: ";
			cin >> key;
			cout << object.find_fibonachi(n, key) + 1 << endl;
			break;
		case '6':
			int t;
			cout << "enter to key: ";
			cin >> t;
			cout << object.find_direct(t) + 1 << endl;
			break;
		case '7':
			object.rand_fill();
			break;
		}
		cout << " time = " << clock() - start << endl;
		cin >> k;
	}
	return 0;
}