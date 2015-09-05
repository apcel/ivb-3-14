#include "unit.hpp"

ai_node* Unit::aimap;
int Unit::MAP_SIZE;

GameObject::GameObject(vec2 position, string texture, Control * base) : Control(texture)
{
	spawn = position;
	this->position = position;
	Control::Transform(
		scaleValue(scaleValueType_absolute, position*(float)object_size),
		scaleValue(scaleValueType_absolute, object_size, object_size));
	base->Attach(this);
}

Unit::Unit(vec2 position, string texture, Control * base, int anim_steap) : Unit(position, texture, base)
{
	anim_count = anim_steap;
	unit_uv = BuildUV(anim_count);
	uvbuffer = unit_uv[0];
}

Unit::Unit(vec2 position, string texture, Control * base) : GameObject(position, texture, base)
{
	if (!anim_count)
		uvbuffer = Control::default_uv;

	coord = position;
	index = coord.x + coord.y * MAP_SIZE;
	memory = vec2(0, 0);
	idle = true;
	ai = nullptr;
}

void
Unit::OnTick(float delta)
{
	if (active) {
		idle = !isFreeDir(dir);
		if (!idle) {
			vec2 d = dir * delta * speed;
			memory += d;

			if (memory.x > 1) {
				coord.x++;
				memory.x--;
				index = coord.x + coord.y * MAP_SIZE;
				updateAI();
			}
			else if (memory.x < -1) {
				coord.x--;
				memory.x++;
				index = coord.x + coord.y * MAP_SIZE;
				updateAI();
			}

			if (memory.y > 1) {
				coord.y++;
				memory.y--;
				index = coord.x + coord.y * MAP_SIZE;
				updateAI();
			}
			else if (memory.y < -1) {
				coord.y--;
				memory.y++;
				index = coord.x + coord.y * MAP_SIZE;
				updateAI();
			}

			position += d;
			Control::Move(scaleValue(scaleValueType_absolute, position*(float)object_size));
		}
		else
			updateAI();

		if (anim_count && !(idle && uv_step == 4)) {
			anim_poll += delta;
			if (anim_poll >= UNIT_ANIM_SPEED) {
				uv_step++;
				if (uv_step == anim_count)
					uv_step = 0;

				uvbuffer = unit_uv[uv_step];
				anim_poll -= UNIT_ANIM_SPEED;
			}
		}
	}
	else
	{
		if (respawn_pool <= 0)
			respawn();
		else
			respawn_pool -= delta;
	}
}

void
Unit::updateAI()
{
	if (ai != nullptr)
		Rotate((*ai)(index, coord, dir));
}

bool
Unit::isFreeDir(vec2 dir)
{
	if (dir.x != 0)	{
		if (abs(coord.y - position.y) > 0.1f)
			return false;
	}else{
		if (abs(coord.x - position.x) > 0.1f)
			return false;
	}
	return aimap[index].isEnableDir(dir);
}

int
Unit::getIndex()
{
	return index;
}

vec2
Unit::getCordinate()
{
	return coord;
}

void
Unit::teleport(vec2 nPos)
{
	coord = nPos;
	position = nPos;
	memory = vec2(0, 0);
	index = coord.x + coord.y * MAP_SIZE;
	Control::Move(scaleValue(scaleValueType_absolute, position*(float)object_size));
	updateAI();
}

void
Unit::respawn()
{
	teleport(spawn);
	active = true;
	visible = true;
}

void
Unit::doRespawn(float time)
{
	die();
	respawn_pool = time;
}

void
Unit::die()
{
	visible = false;
	active = false;
	idle = true;
	respawn_pool = RESPAWN_TIME;
}

void
Unit::Rotate(vec2 dir)
{
	if (vRotate_enable) {
		if (dir == vec2(-1, 0))
			Control::Rotate(PI);
		else if (dir == vec2(0, 1))
			Control::Rotate(PI / 2);
		else if (dir == vec2(0, -1))
			Control::Rotate(3 * PI / 2);
		else
			Control::Rotate(0);
	}

	this->dir = dir;
}

void
Unit::Init(int MAP_SIZE)
{
	Unit::MAP_SIZE = MAP_SIZE;
}

Unit::~Unit()
{
	if (anim_count) {
		for (int i = 0; i < anim_count; i++)
			glDeleteBuffers(0, &unit_uv[i]);
		delete unit_uv;
	}

	if (ai != nullptr)
		delete ai;
}