#include "Window.hpp"

Window::Window()
{
	w_close_event += {reinterpret_cast<IDelegate*>(this), static_cast<void(IDelegate::*)(Control *)>(&Window::w_end)};
}

void
Window::w_end(Control * win)
{
	visible = true;
}

void
Window::openWindow(Window * win, bool hide_this)
{
	if (hide_this)
		visible = false;

	for (auto i = w_close_event.keys.begin(); i != w_close_event.keys.end(); i++)
		win->onDestroy += (*i);
	base->Attach(win);
}

void
Window::BindButton(char * button, char * text, void(IDelegate::* onClick)(Control *))
{
	Button * b = dynamic_cast<Button*>(sender->getByNameFirst(button)->controls[0]);
	if (b == nullptr) {
		cout << "Error. Window: control '" << button << "' not found or not 'Button' type\n";
		return;
	}

	b->onMouseClick += {reinterpret_cast<IDelegate*>(this), onClick};

	if (text == nullptr)
		return;

	auto elements = b->getByName(btn_mask);
	for (auto c = elements.begin(); c != elements.end(); c++)
		dynamic_cast<Laber*>(*c)->setText(text);
}

void
Window::BindCheckBox(char * checkbox, char * text, void(IDelegate::* onSetValue)(CheckBox::Key *), bool state)
{
	CheckBox * b = dynamic_cast<CheckBox*>(sender->getByNameFirst(checkbox));
	if (b == nullptr) {
		cout << "Error. Window: control '" << checkbox << "' not found or not 'CheckBox' type\n";
		return;
	}
	BindCheckBox(b, text, onSetValue, state);
}

void
Window::BindCheckBox(CheckBox * b, char * text, void(IDelegate::* onSetValue)(CheckBox::Key *), bool state)
{
	b->set(state);
	b->onCheck += {reinterpret_cast<IDelegate*>(this), onSetValue};

	if (text == nullptr)
		return;

	Laber * l = dynamic_cast<Laber*>(b->getByNameFirst(btn_mask));
	if (l != nullptr)
		l->setText(text);
}