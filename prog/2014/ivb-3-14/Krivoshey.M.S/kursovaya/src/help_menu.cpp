#include "help_menu.hpp"

help_menu::help_menu()
{
	sender = Control::loadFromFile("Data\\gui\\help_menu.gui");
	Attach(sender);

	BindButton("exit", "Назад", static_cast<void(IDelegate::*)(Control *)>(&help_menu::exit));
}

void
help_menu::exit(Control * sender)
{
	die();
}