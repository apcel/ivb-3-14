#include "hendel.h"

#ifndef __game_end
#define __game_end
class game_end : public Window
{
	void replay(Control * sender);
	void exit(Control * sender);
public:
	bool needClose = false;
	game_end(bool victory);
};
#endif