#include "hendel.h"

#ifndef __setting_menu
#define __setting_menu
class setting_menu : public Window
{
	void d_fps(CheckBox::Key* key);
	void d_anim(CheckBox::Key* key);
	void d_sse(CheckBox::Key* key);
	void exit(Control * sender);
public:
	setting_menu();
};
#endif