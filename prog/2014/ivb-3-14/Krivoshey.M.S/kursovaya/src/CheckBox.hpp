#include "hendel.h"

#ifndef __checkbox
#define __checkbox
class CheckBox : public Control
{
	bool value;
	void OnCheck();

	void on(Control * btn);
	void off(Control * btn);
public:
	Button * state_off;
	Button * state_on;
	struct Key
	{
		CheckBox * sender;
		bool value;
	};

	Delegate<Key> onCheck;

	void set(bool enable, bool permonent = false);
	bool get();
	void Bind(Button * state, bool flag);

	CheckBox();
};
#endif