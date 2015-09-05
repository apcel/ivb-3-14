#include "pause_menu.hpp"

pause_menu::pause_menu()
{
	sender = Control::loadFromFile("Data\\gui\\pause_menu.gui");
	Attach(sender);

	BindButton("contine", "Продолжить", static_cast<void(IDelegate::*)(Control *)>(&pause_menu::contine));
	BindButton("exit", "Выйти", static_cast<void(IDelegate::*)(Control *)>(&pause_menu::exit));
}

void
pause_menu::contine(Control * sender)
{
	die();
}

void
pause_menu::exit(Control * sender)
{
	needClose = true;
	die();
}