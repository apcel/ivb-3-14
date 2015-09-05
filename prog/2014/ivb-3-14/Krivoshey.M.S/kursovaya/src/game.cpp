#include "game.hpp"

bool game::pause = false;
int game::border_mask[] = { 2, 7, 3, 6, 0, 15, 11, 5, 12, 8, 4, 1, 9, 14, 13, 10 };

game::game(char * level)
{
	sender = Control::loadFromFile("Data\\gui\\game.gui");

	game_plane = sender->getByNameFirst("game_plane");
	if (game_plane == nullptr) {
		cout << "Error. Game gui not have 'game_plane' control.";
		return;
	}

	background = sender->getByNameFirst("background");
	border_plane = game_plane->getByNameFirst("border_plane");
	live_text = dynamic_cast<Laber*>(sender->getByNameFirst("live"));
	score_text = dynamic_cast<Laber*>(sender->getByNameFirst("score"));
	bonus_text = dynamic_cast<Laber*>(sender->getByNameFirst("bonus"));
	bonus_t_text = dynamic_cast<Laber*>(sender->getByNameFirst("bonus_t"));

	scaleValue sc = scaleValue(scaleValueType_absolute, object_size, object_size);
	key_old = new bool[KEY_REG];
	player = nullptr;

	ifstream map(level, ios::binary | ios::in);
	int offest = 0;
	Unit *u;
	char b;

	map.read(&b, sizeof b);
	MAP_SIZE = b;
	MAP_SIZE_2 = MAP_SIZE*MAP_SIZE;

	border = new Control*[MAP_SIZE_2];
	gameobject = new GameObject*[MAP_SIZE_2];
	aimap = new ai_node[MAP_SIZE_2];
	aimap_pl = new ai_node[MAP_SIZE_2];

	if (setting::instance->anim_points)
		point_a = new float[MAP_SIZE_2];

	Unit::Init(MAP_SIZE);
	Unit::aimap = aimap;

	for (int y = 0; y < MAP_SIZE; y++) {
		for (int x = 0; x < MAP_SIZE; x++, offest++) {
			gameobject[offest] = nullptr;
			border[offest] = nullptr;
			point_a[offest] = 0;

			map.read(&b, sizeof b);
			switch (b)
			{
			case '1':
				border[offest] = new Control("Data\\textures\\object\\block.dds");
				border[offest]->Transform(scaleValue(scaleValueType_absolute, object_size * x, object_size * y), sc);
				border_plane->Attach(border[offest]);
				break;
			case '2':
				gameobject[offest] = new GameObject(vec2(x, y), "Data\\textures\\object\\point.dds", game_plane);
				if (setting::instance->anim_points)
					point_a[offest] = GetRandom(-PI, PI);
				total_score++;
				break;
			case '3':
				player = new Unit(vec2(x, y), "Data\\textures\\object\\pacman.dds", game_plane, 8);
				player->speed = PLAYER_SPEED;
				player->Rotate(vec2(0, -1));
				break;
			case '4':
				u = new Unit(vec2(x, y), string("Data\\textures\\object\\mob") + (char)('0' + (int)GetRandom(0, 3)) + string(".dds"), game_plane);
				u->vRotate_enable = false;
				u->Rotate(vec2(0, -1));
				mobs.push_back(u);
				break;
			case '5':
				gameobject[offest] = new GameObject(vec2(x, y), "Data\\textures\\object\\portal.dds", game_plane);
				gameobject[offest]->specal = 1;
				break;
			case '6':
				gameobject[offest] = new GameObject(vec2(x, y), "Data\\textures\\object\\bonus.dds", game_plane);
				gameobject[offest]->specal = 2;
				break;
			}

			map.read(&b, sizeof b);
			aimap[offest] = ai_node(b);
			aimap_pl[offest] = ai_node(b);
		}
	}
	map.close();

	if (player == nullptr) {
		cout << "Error. Map '" << level << "' not have player spawn point.";
		return;
	}

	border_uv = BuildUV(BORDER_UV_COUNT);
	int index = 0;
	Control* c;
	for (int y = 0; y < MAP_SIZE; y++) {
		for (int x = 0; x < MAP_SIZE; x++, index++) {
			bool right = enableBlock(x + 1, y);
			bool left = enableBlock(x - 1, y);
			bool down = enableBlock(x, y + 1);
			bool up = enableBlock(x, y - 1);

			if (enableBlock(x, y)) {
				int i = right * 8 + left * 4 + down * 2 + up;
				border[index]->uvbuffer = border_uv[border_mask[i]];
			}

			if (setting::instance->debug_show_ai) {
				c = new Control("Data\\textures\\object\\ai.dds");
				c->Transform(scaleValue(scaleValueType_absolute, object_size * x, object_size * y), sc);
				c->uvbuffer = border_uv[border_mask[aimap[index].toChar()]];
				game_plane->Attach(c);
			}
		}
	}

	queue<AI_normal*> build_ai;
	build_ai.push(new AI_normal(aimap, MAP_SIZE, 1));
	float timme_offest = 0;

	for (auto i = mobs.begin(); i != mobs.end(); i++) {
		(*i)->MoveToTop();
		(*i)->doRespawn(timme_offest);
		timme_offest += 3.0f;

		if (!build_ai.empty()) {
			(*i)->ai = build_ai.front();
			build_ai.pop();
		} else
			(*i)->ai = new AI_normal(aimap, MAP_SIZE);
	}

	player_fx = createFX(sender, true);
	player->MoveToTop();
	task = vec2(0, 0);

	renderBackground();

	scale = scaleValue(scaleValueType_window, 1, 1);
	Attach(sender);

	UpdateTransform(true);
	pause = false;
}

Particle::EmitterPoint*
game::createFX(Control * sender, bool player)
{
	auto p = new Particle::ParticleSystem();
	auto em = new Particle::EmitterPoint();
	em->limit = 500;
	em->rotation = { -PI, PI };

	if (player) {
		p->texture = TextureManager::load("Data\\textures\\fire.dds")->uint;
		em->scale = scaleValue(scaleValueType_absolute, 32, 32);
	} else {
		//p->texture = TextureManager::load("Data\\textures\\fog.dds")->uint;
		//em->scale = scaleValue(scaleValueType_absolute, 48, 48);
		//em->color_alpha = { 0.8f, 0.9f };
	}
	
	p->emitters.push_back(em);
	p->affectors.push_back(new Particle::AffectorColor(-0.01f));
	p->affectors.push_back(new Particle::AffectorRotation(0.01f));
	sender->Attach(p);
	return em;
}

bool
game::enableBlock(int x, int y)
{
	if (x < 0 || y < 0 || x >= MAP_SIZE || y >= MAP_SIZE)
		return false;
	return border[x + y*MAP_SIZE] != nullptr;
}

void
game::OnTick(float delta)
{
	for (int i = 0; i < KEY_REG; i++) {
		bool value = Control::key_state[i];

		if (value && !key_old[i])
			OnKeyDown(i);

		key_old[i] = value;
	}

	if (pause)
		return;

	if (setting::instance->anim_points) {
		for (int i = 0; i < MAP_SIZE_2; i++) {
			if (gameobject[i] != nullptr && gameobject[i]->specal == 0) {
				point_a[i] += delta;
				gameobject[i]->colorMult = vec4(1, 1, 1, 0.75f + sin(point_a[i]) / 4.0f);
			}
		}
	}

	if (player->isFreeDir(task)) {
		player->Rotate(task);
		task = vec2(0, 0);
	}

	player->OnTick(delta);
	
	vec2 pl_pos = player->getCordinate();
	int pl_index = player->getIndex();

	if (bonus) {
		bonus_t_text->visible = true;
		bonus -= tickDelta;

		char * temp = new char[20];
		sprintf(temp, "%.1f", bonus);
		bonus_text->setText(temp);
		delete[] temp;

		if (bonus <= 0) {
			bonus = 0;
			player->colorMult = vec4(1, 1, 1, 1);
		}
	} else
		bonus_t_text->visible = false;

	bonus_text->visible = bonus_t_text->visible;
	updateFX(player_fx, player, bonus);

	int old_score = score;
	if (gameobject[pl_index] != nullptr) {
		switch (gameobject[pl_index]->specal)
		{
		case 1:
			for (int i = 0; i < MAP_SIZE_2; i++) {
				if (pl_index != i && gameobject[i] != nullptr && gameobject[i]->specal == 1) {
					player->teleport(gameobject[i]->position + player->dir);
					break;
				}
			}
			break;
		case 2:
			bonus = BONUS_TIME;
			player->colorMult = vec4(1, 0.5, 0.5, 1);
			gameobject[pl_index]->visible = false;
			gameobject[pl_index] = nullptr;
			score += 150;
			break;
		case 0:
			gameobject[pl_index]->die();
			gameobject[pl_index] = nullptr;
			score_only++;
			score += 50;

			if (score_only == total_score) {
				end(true);
				return;
			}
			break;
		}
	}

	for (int i = 0; i < mobs.size(); i++) {
		Unit * mob = mobs[i];
		if (mob->active) {
			int index = mob->getIndex();
			if (pl_index == index) {
				if (bonus) {
					score += 200;
					mob->die();
				}
				else
				{
					live--;
					if (live != 0) {
						player->respawn();
						for (auto n = mobs.begin(); n != mobs.end(); n++)
							(*n)->respawn();

						char * temp = new char[32];
						sprintf(temp, "x%i", live);
						live_text->setText(temp);
						delete[] temp;
						break;
					} else {
						end(false);
						return;
					}
				}
				break;
			}
		}
		dynamic_cast<AI_normal*>(mob->ai)->player_information = { pl_index, player->dir, bonus };
		mob->OnTick(delta);
	}

	if (old_score != score) {
		char * temp = new char[5];
		sprintf(temp, "%i", score);
		score_text->setText(temp);
		delete temp;
	}
}

void
game::updateFX(Particle::EmitterPoint* em, Unit * unit, bool enable)
{
	if (enable) {
		em->count = 1;
		em->point = scaleValue(scaleValueType_window, unit->getPos(scaleValueType_window));
		em->point.value += unit->getScale(scaleValueType_window) / 2.0f;
	} else
		em->count = 0;
}

void
game::OnKeyDown(int key)
{
	switch (key)
	{
	case GLFW_KEY_D:
	case GLFW_KEY_RIGHT:
		task = vec2(1, 0);
		break;
	case GLFW_KEY_A:
	case GLFW_KEY_LEFT:
		task = vec2(-1, 0);
		break;
	case GLFW_KEY_W:
	case GLFW_KEY_UP:
		task = vec2(0, -1);
		break;
	case GLFW_KEY_S:
	case GLFW_KEY_DOWN:
		task = vec2(0, 1);
		break;
	case GLFW_KEY_SPACE:
		if (pause_m == nullptr)
			pause = !pause;
		break;
	case GLFW_KEY_ESCAPE:
		if (pause_m == nullptr) {
			pause = true;
			pause_m = new pause_menu();
			pause_m->onDestroy += {reinterpret_cast<IDelegate*>(this), static_cast<void(IDelegate::*)(Control *)>(&game::onPauseEnd)};
			base->Attach(pause_m);
		}
		else
			pause_m->die();
		break;
	}
}

void
game::end(bool victory)
{
	game_end* ge = new game_end(victory);
	ge->onDestroy = onDestroy;
	base->Attach(ge);
	onDestroy.keys.clear();
	die();
}

void
game::onPauseEnd(Control * menu)
{
	bool need = pause_m->needClose;
	pause_m = nullptr;
	pause = false;

	if (need)
		die();
}

void
game::Render()
{
	Control::Render();
	OnTick(Control::tickDelta);
}

void
game::UpdateTransform(bool updateChildren)
{
	Control::UpdateTransform(updateChildren);
	renderBackground();
}

void
game::renderBackground()
{
	if (background->texture != -1)
		glDeleteTextures(1, &background->texture);

	border_plane->visible = true;
	background->texture = border_plane->renderToTexture();
	border_plane->visible = false;
}