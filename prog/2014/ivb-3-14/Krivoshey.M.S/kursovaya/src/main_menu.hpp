#include "hendel.h"

#ifndef __main_menu
#define __main_menu
class main_menu : public Window
{
	struct Key {
		vec2 position;
		Control* control;
	};

	float time;
	vector<Key>mobs;
	vector<Key>eye;

	void play(Control * sender);
	void opt(Control * sender);
	void help(Control * sender);
	void sdk(Control * sender);
	void exit(Control * sender);
	void Render();

	public:
		static bool needExit;
		main_menu();
};
#endif