#include "hendel.h"

#ifndef __window
#define __window
class Window : public Control
{
protected:
	Control * sender;
	Delegate<Control> w_close_event;

	const char * btn_mask = "text";

	void w_end(Control * win);
	void openWindow(Window * win, bool hide_this = true);
	void BindButton(char * button, char * text, void(IDelegate::* onClick)(Control *));
	void BindCheckBox(char * checkbox, char * text, void(IDelegate::* onSetValue)(CheckBox::Key *), bool state);
	void BindCheckBox(CheckBox * b, char * text, void(IDelegate::* onSetValue)(CheckBox::Key *), bool state);
public:
	Window();
};
#endif