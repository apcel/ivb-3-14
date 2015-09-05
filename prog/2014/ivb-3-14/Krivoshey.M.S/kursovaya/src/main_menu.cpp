#include "main_menu.hpp"
bool main_menu::needExit = false;

main_menu::main_menu()
{
	sender = Control::loadFromFile("Data\\gui\\mainmenu.gui");
	Attach(sender);

	Control * background = sender->getByNameFirst("background");
	for each (Control* i in background->controls)
	{
		mobs.push_back({ i->getPosition().get(scaleValueType_absolute), i });
		for each (Control * j in i->controls)
			eye.push_back({ j->getPosition().get(scaleValueType_absolute), j });
	}

	BindButton("play", "Играть", static_cast<void(IDelegate::*)(Control *)>(&main_menu::play));
	BindButton("opt", "Настройки", static_cast<void(IDelegate::*)(Control *)>(&main_menu::opt));
	BindButton("sdk", "Редактор", static_cast<void(IDelegate::*)(Control *)>(&main_menu::sdk));
	BindButton("help", "Помощь", static_cast<void(IDelegate::*)(Control *)>(&main_menu::help));
	BindButton("exit", "Выйти", static_cast<void(IDelegate::*)(Control *)>(&main_menu::exit));
}

void
main_menu::Render()
{
	time += Control::tickDelta*5;
	float d = 0;

	for (auto i = mobs.begin(); i != mobs.end(); i++) {
		d += 0.4f;
		i->control->Move(scaleValue(scaleValueType_absolute, i->position.x, i->position.y + sin(d + time) * 35));
	}
	
	for (auto i = eye.begin(); i != eye.end(); i++) {
		vec2 pos = i->position;
		vec2 delta = screenToPixel(mouse_pos) - i->control->getPos(scaleValueType_absolute) - (i->control->getScale(scaleValueType_absolute)/2.0f);
		delta /= sqrt(delta.x*delta.x + delta.y*delta.y);
		pos += delta * vec2(5.0f, 9.0f);

		i->control->Move(scaleValue(scaleValueType_absolute, pos.x, pos.y));
	}

	Control::Render();
}

void
main_menu::play(Control * sender)
{
	openWindow((Window*)new game(setting::instance->GAME_LEVEL));
}

void
main_menu::sdk(Control * sender)
{
	openWindow((Window*)new level_editor(setting::instance->GAME_LEVEL));
}

void
main_menu::help(Control * sender)
{
	openWindow((Window*)new help_menu());
}

void
main_menu::opt(Control * sender)
{
	openWindow((Window*)new setting_menu());
}

void
main_menu::exit(Control * sender)
{
	needExit = true;
}