#include "setting_menu.hpp"

setting_menu::setting_menu()
{
	sender = Control::loadFromFile("Data\\gui\\setting.gui");
	Attach(sender);

	BindCheckBox("fps", "Показывать FPS", static_cast<void(IDelegate::*)(CheckBox::Key *)>(&setting_menu::d_fps), setting::instance->show_fps);
	BindCheckBox("sse", "Постобрабодка кадра", static_cast<void(IDelegate::*)(CheckBox::Key *)>(&setting_menu::d_sse), setting::instance->sse);
	BindCheckBox("anim", "Анимировать монетки", static_cast<void(IDelegate::*)(CheckBox::Key *)>(&setting_menu::d_anim), setting::instance->anim_points);

	BindButton("exit", "Назад", static_cast<void(IDelegate::*)(Control *)>(&setting_menu::exit));
}

void
setting_menu::d_fps(CheckBox::Key *key)
{
	setting::instance->show_fps = key->value;
}

void
setting_menu::d_anim(CheckBox::Key *key)
{
	setting::instance->anim_points = key->value;
}

void
setting_menu::d_sse(CheckBox::Key *key)
{
	setting::instance->sse = key->value;
}

void
setting_menu::exit(Control * sender)
{
	die();
}