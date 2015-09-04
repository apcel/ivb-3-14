#include "setting.hpp"

setting* setting::instance = nullptr;

setting::setting()
{
	GAME_LEVEL = "Data\\level\\level_1.map";
	sse = true;
	anim_points = true;
	show_fps = true;

	/*DEBUG*/
	debug_show_ai = false;

	instance = this;
}