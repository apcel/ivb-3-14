#include "CheckBox.hpp"

CheckBox::CheckBox()
{
	state_on = nullptr;
	state_off = nullptr;
}

void
CheckBox::Bind(Button * state, bool flag)
{
	if (flag) {
		state_on = state;
		state_on->onMouseClick += {reinterpret_cast<IDelegate*>(this), static_cast<void(IDelegate::*)(Control *)>(&CheckBox::on)};
	} else {
		state_off = state;
		state_off->onMouseClick += {reinterpret_cast<IDelegate*>(this), static_cast<void(IDelegate::*)(Control *)>(&CheckBox::off)};
	}
}

void
CheckBox::off(Control * btn)
{
	set(true);
}

void
CheckBox::on(Control * btn)
{
	set(false);
}

void
CheckBox::set(bool enable, bool permonent)
{
	value = enable;
	if (state_on != nullptr)
		state_on->visible = value;
	if (state_off != nullptr)
		state_off->visible = !value;

	if (!permonent) {
		Key k;
		k.sender = this;
		k.value = value;
		onCheck(&k);
	}
}

bool
CheckBox::get()
{
	return value;
}