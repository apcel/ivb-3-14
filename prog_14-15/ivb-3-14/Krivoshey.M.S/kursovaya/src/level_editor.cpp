#include "level_editor.hpp"

level_editor::level_editor(char * level)
{
	map_name = level;
	sender = Control::loadFromFile("Data\\gui\\level_editor.gui");
	Control * edit_plane = sender->getByNameFirst("edit_plane");
	Attach(sender);

	ifstream map(level, ios::binary | ios::in);
	int offest = 0;
	char b;
	Control * c;
	scaleValue sc = scaleValue(scaleValueType_absolute, object_size, object_size);

	map.read(&b, sizeof b);
	MAP_SIZE = b;
	MAP_SIZE_2 = MAP_SIZE*MAP_SIZE;
	Map = new Slot[MAP_SIZE_2];

	for (int y = 0; y < MAP_SIZE; y++) {
		for (int x = 0; x < MAP_SIZE; x++, offest++) {
			map.read(&b, sizeof b);
			c = new Control();
			c->Transform(scaleValue(scaleValueType_absolute, object_size*x, object_size*y), sc);
			c->onMouseDown += {reinterpret_cast<IDelegate*>(this), static_cast<void(IDelegate::*)(Control *)>(&level_editor::map_mouse)};
			Map[offest] = { b-'0', c };
			edit_plane->Attach(c);
			map.read(&b, sizeof b);
		}
	}

	Unit::Init(MAP_SIZE);
	border_uv = BuildUV(BORDER_UV_COUNT);
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++)
			updatePoint(x, y);
	}

	br.push_back(reinterpret_cast<CheckBox*>(sender->getByNameFirst("br_border")));
	br.push_back(reinterpret_cast<CheckBox*>(sender->getByNameFirst("br_point")));
	br.push_back(reinterpret_cast<CheckBox*>(sender->getByNameFirst("br_mob")));
	br.push_back(reinterpret_cast<CheckBox*>(sender->getByNameFirst("br_bonus")));
	br.push_back(reinterpret_cast<CheckBox*>(sender->getByNameFirst("br_player")));
	br.push_back(reinterpret_cast<CheckBox*>(sender->getByNameFirst("br_portal")));
	br.push_back(reinterpret_cast<CheckBox*>(sender->getByNameFirst("br_blank")));

	BindCheckBox("show_ai", "Показать AI карту", static_cast<void(IDelegate::*)(CheckBox::Key *)>(&level_editor::show_ai), false);

	for (auto i = br.begin(); i != br.end(); i++)
		BindCheckBox(*i, nullptr, static_cast<void(IDelegate::*)(CheckBox::Key*)>(&level_editor::br_check), false);

	BindButton("exit", "Выход", static_cast<void(IDelegate::*)(Control *)>(&level_editor::exit));
}

bool
level_editor::enableBlock(int x, int y)
{
	if (x < 0 || y < 0 || x >= MAP_SIZE || y >= MAP_SIZE)
		return false;
	return Map[x + y*MAP_SIZE].id == 1;
}

bool
level_editor::enablePoint(int x, int y)
{
	if (x < 0 || y < 0 || x >= MAP_SIZE || y >= MAP_SIZE)
		return false;
	return Map[x + y*MAP_SIZE].id != 1;
}

void
level_editor::updatePoint(int x, int y)
{
	updatePoint(x, y, Map[x + y* MAP_SIZE].id);
}

void
level_editor::updatePoint(int x, int y, int v)
{
	if (x < 0 || y < 0 || x >= MAP_SIZE || y >= MAP_SIZE)
		return;

	int index = x + y* MAP_SIZE;
	bool right, left, down, up;
	Control * c = Map[index].control;
	c->uvbuffer = Control::default_uv;
	c->_rendable = true;

	switch (v) {
	case 0:
		c->_rendable = false;
	case 1:
		c->texture = TextureManager::load("Data\\textures\\object\\block.dds")->uint;

		right = enableBlock(x + 1, y);
		left = enableBlock(x - 1, y);
		down = enableBlock(x, y + 1);
		up = enableBlock(x, y - 1);

		c->uvbuffer = border_uv[game::border_mask[right * 8 + left * 4 + down * 2 + up]];
		break;
	case 2:
		c->texture = TextureManager::load("Data\\textures\\object\\point.dds")->uint;
		break;
	case 3:
		c->texture = TextureManager::load("Data\\textures\\object\\pacman.dds")->uint;
		c->uvbuffer = BuildUV("0 0 0.33 0.33");
		break;
	case 4:
		c->texture = TextureManager::load("Data\\textures\\object\\mob0.dds")->uint;
		break;
	case 5:
		c->texture = TextureManager::load("Data\\textures\\object\\portal.dds")->uint;
		break;
	case 6:
		c->texture = TextureManager::load("Data\\textures\\object\\bonus.dds")->uint;
		break;
	}
	if (Map[index].id != v) {
		Map[index].id = v;

		updatePoint(x - 1, y);
		updatePoint(x + 1, y);
		updatePoint(x, y - 1);
		updatePoint(x, y + 1);

		needSave = true;
	}
}

void
level_editor::map_mouse(Control * sender)
{
	if (brash == -1)
		return;

	vec2 p = sender->getPos(scaleValueType_absolute);
	p -= sender->base->getPos(scaleValueType_absolute);
	p /= object_size;
	updatePoint(p.x, p.y, brash);
}

void
level_editor::br_check(CheckBox::Key *key)
{
	for (auto i = br.begin(); i != br.end(); i++) {
		if ((*i)->name != key->sender->name)
			(*i)->set(false, true);
	}

	if (key->value) {
		if (key->sender->name == "br_border")
			brash = 1;
		else if (key->sender->name == "br_point")
			brash = 2;
		else if (key->sender->name == "br_player")
			brash = 3;
		else if (key->sender->name == "br_mob")
			brash = 4;
		else if (key->sender->name == "br_portal")
			brash = 5;
		else if (key->sender->name == "br_bonus")
			brash = 6;
		else if (key->sender->name == "br_blank")
			brash = 0;
		else
			brash = -1;
	}
	else
		key->sender->set(true, true);
}

void
level_editor::exit(Control * sender)
{
	if (needSave)
		openWindow(
			(Window*)new dlg_YesNo("Сохранить изменения?",
			reinterpret_cast<IDelegate*>(this),
			static_cast<void(IDelegate::*)(Control *)>(&level_editor::exit_save)), false);
	else
		die();
}

void
level_editor::exit_save(Control * sender)
{
	if (reinterpret_cast<dlg_YesNo*>(sender)->result) {
		if (!isNormalMap())
			return; 
		save();
	}
	die();
}

bool
level_editor::isNormalMap()
{
	int pl_count = 0;
	int point_count = 0;
	int portal_count = 0;
	for (int index = 0; index < MAP_SIZE_2; index++)
	{
		switch (Map[index].id)
		{
		case 2:
			point_count++;
			break;
		case 3:
			pl_count++;
			break;
		case 5:
			portal_count++;
			break;
		}
	}

	if (pl_count != 1) {
		cout << "Build map error: player spawn can be only one.\n";
		return false;
	}
	if (point_count == 1) {
		cout << "Build map error: must be at least one 'Point'.\n";
		return false;
	}
	if (portal_count != 0 && portal_count != 2) {
		cout << "Build map error: if portals exist, they should be 2.\n";
		return false;
	}

	return true;
}

void
level_editor::save()
{
	cout << "Save map '" << map_name << "'.";

	ofstream save_map(map_name, ios::binary | ios::out);
	int index = 0;
	save_map << (char)MAP_SIZE;
	for (int y = 0; y < MAP_SIZE; y++) {
		for (int x = 0; x < MAP_SIZE; x++, index++)	{
			char c = 0;
			if (!enableBlock(x, y)) {
				bool right = enablePoint(x + 1, y);
				bool left = enablePoint(x - 1, y);
				bool down = enablePoint(x, y + 1);
				bool up = enablePoint(x, y - 1);

				c = up | (down << 1) | (left << 2) | (right << 3);
			}
			save_map << Map[index].id << c;
		}
	}
	save_map.close();
	cout << " Done." << std::endl;
}

void 
level_editor::show_ai(CheckBox::Key* key)
{
	if (key->value) {
		int index = 0;
		for (int y = 0; y < MAP_SIZE; y++) {
			for (int x = 0; x < MAP_SIZE; x++, index++)	{
				char c = 0;
				if (!enableBlock(x, y)) {
					bool right = enablePoint(x + 1, y);
					bool left = enablePoint(x - 1, y);
					bool down = enablePoint(x, y + 1);
					bool up = enablePoint(x, y - 1);
					c = right * 8 + left * 4 + down * 2 + up;
				}

				Map[index].control->texture = TextureManager::load("Data\\textures\\object\\ai.dds")->uint;
				Map[index].control->uvbuffer = border_uv[game::border_mask[c]];
				Map[index].control->_rendable = true;
			}
		}
	}
	else
	{
		for (int y = 0; y < MAP_SIZE; y++) {
			for (int x = 0; x < MAP_SIZE; x++)
				updatePoint(x, y);
		}
	}
}