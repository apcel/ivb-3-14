#include "hendel.h"

#ifndef __pause_menu
	#define __pause_menu
class pause_menu : public Window
	{
		void contine(Control * sender);
		void exit(Control * sender);
	public:
		bool needClose = false;
		pause_menu();
	};
#endif