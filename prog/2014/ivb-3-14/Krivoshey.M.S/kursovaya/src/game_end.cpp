#include "game_end.hpp"

game_end::game_end(bool victory)
{
	sender = Control::loadFromFile("Data\\gui\\game_end.gui");
	sender->getByNameFirst("victory")->visible = victory;
	sender->getByNameFirst("dead")->visible = !victory;
	Attach(sender);

	BindButton("replay", "Переиграть", static_cast<void(IDelegate::*)(Control *)>(&game_end::replay));
	BindButton("exit", "В меню", static_cast<void(IDelegate::*)(Control *)>(&game_end::exit));
}

void
game_end::replay(Control * sender)
{
	game* g = new game(setting::instance->GAME_LEVEL);
	g->onDestroy = onDestroy;
	base->Attach(g);
	onDestroy.keys.clear();

	die();
}

void
game_end::exit(Control * sender)
{
	die();
}