#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <time.h>
#include <string>
#include <sstream>
#include <windows.h>
#include <vector>

using namespace std;

struct event {
	string input;
	string message;
};

void 
Sleep (BYTE time)
{
	return Sleep((DWORD)time * 1000);
}


int 
main()
{
	int k = 1;
	event i;
	vector<event> event_list;
	while (true) {		
		cout << "Event #" << k << '\n';
		cout << "Enter time (format: 'hh:mm')\n";
		getline(cin, i.input);
		if (i.input == "Enough")
			break;
		cout << "Enter message\n";
		getline(cin, i.message);
		cout << "Ok. Event #" << k << " is ready" << '\n';
		event_list.push_back(i);
		k++;
		cout << "Write \"Enough\" to begin\n";
	}
	std::string my_time;

	do {
		std::stringstream ss;
		time_t t;
		struct tm *t_m;
		t = time(NULL);
		t_m = localtime(&t);
		ss << t_m->tm_hour << ':' << t_m->tm_min;
		ss >> my_time;
		bool r = 1;
		while (r) {
			r = 0;
			for (auto i = event_list.begin(); i != event_list.end(); i++) {
				if ((*i).input == my_time) {
					cout << (*i).message << '\n';
					cout << '\a';
					event_list.erase(i);
					r = 1;
					break;
				}
			}
		}
		Sleep((BYTE)1);
	} while (event_list .size()!=0);
	
	system("pause");
	return 0;
}