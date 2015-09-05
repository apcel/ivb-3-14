#include "ai.hpp"

vec2 AI::DIR[] = { vec2(1, 0), vec2(0, -1), vec2(-1, 0), vec2(0, 1) };

ai_node::ai_node(char c)
{
	up = c & 1;
	down = c & 2;
	left = c & 4;
	right = c & 8;
}

char
ai_node::toChar()
{
	return right * 8 + left * 4 + down * 2 + up;
}

bool
ai_node::isEnableDir(vec2 dir)
{
	if (dir == vec2(-1, 0))
		return left;
	else if (dir == vec2(0, 1))
		return down;
	else if (dir == vec2(0, -1))
		return up;
	else if (dir == vec2(1, 0))
		return right;

	return false;
}

int
ai_node::weight()
{
	return left + down + right + up;
}

/*======================================PATH MANAGER===================================*/
/*=====================================================================================*/

PathManager::PathManager(bool * map, int size)
{
	this->map = map;
	this->size = size;
	size2 = size*size;

	map_wave = new int[size2];
}

void
PathManager::bind(int index, std::queue<int> * array, int level)
{
	if (index >= 0 && index < size2 &&
		map[index] && map_wave[index] == -2){
		array->push(index);
		map_wave[index] = level;
	}
}

queue<int>
PathManager::get(int index_start, int index_end)
{
	int next;
	int index;
	queue<int> q;
	queue<int> temp;
	queue<int> result;

	temp.push(index_start);

	for (int i = 0; i < size2; i++)
		map_wave[i] = -2;

	do
	{
		temp.swap(q);

		while (!q.empty()) {
			index = q.front();
			if (index == index_end)
				break;

			next = map_wave[index] + 1;
			bind(index + 1, &temp, next);
			bind(index - 1, &temp, next);
			bind(index + size, &temp, next);
			bind(index - size, &temp, next);
			q.pop();
		}
	} while (!temp.empty());

	next = map_wave[index];
	if (next != -2)
		result.push(index);
	while (next >= 0) {
		next--;

		if (map_wave[index - 1] == next)
			index--;
		else if (map_wave[index + 1] == next)
			index++;
		else if (map_wave[index + size] == next)
			index += size;
		else
			index -= size;

		result.push(index);
	}

	return result;
}

PathManager::~PathManager()
{
	delete[] map;
	delete[] map_wave;
}

/*======================================AI=============================================*/
/*====================================SIMPLE===========================================*/

AI_simple::AI_simple(ai_node* aimap)
{
	this->aimap = aimap;
}

vec2
AI_simple::operator()(int index, vec2 pos, vec2 old_dir)
{
	if (aimap[index].weight() < 3 && aimap[index].isEnableDir(old_dir))
		return old_dir;

	vec2 dir;
	do
	{
		dir = DIR[(int)GetRandom(0, 4)];
	} while (dir == old_dir && !aimap[index].isEnableDir(dir));
	return dir;
}

/*======================================AI=============================================*/
/*====================================NORMAL===========================================*/

AI_normal::AI_normal(ai_node* aimap, int size, int mode)
{
	invalid = false;
	logic_type = mode;
	this->aimap = aimap;

	int size2 = size*size;
	bool * map = new bool[size2];
	for (int i = 0; i < size2; i++)
		map[i] = aimap[i].weight() != 0;

	ph = new PathManager(map, size);
}

vec2
AI_normal::operator()(int index, vec2 pos, vec2 old_dir)
{
	if (player_information.enrage) {
		if (!enrage) {
			enrage = true;
			return old_dir * -1.0f;
		}
		vec2 dir;
		do
		{
			dir = DIR[(int)GetRandom(0, 4)];
		} while (dir == old_dir && !aimap[index].isEnableDir(dir));
		return dir;
	}

	enrage = false;

	int go_to;
	switch (logic_type) {
	case 1:
			if (player_information.dir == vec2(-1, 0))
				go_to = player_information.index - 3;
			else if (player_information.dir == vec2(0, 1))
				go_to = player_information.index + ph->size * 3;
			else if (player_information.dir == vec2(0, -1))
				go_to = player_information.index - ph->size * 3;
			else
				go_to = player_information.index + 3;

			go_to = clamp<int>(go_to, 0, ph->size*ph->size);

			history.push(go_to);
		break;
	default:
		go_to = player_information.index;
		break;
	}

	queue<int> path = ph->get(index, go_to);
	if (!path.empty()) {
		int i = path.back();

		invalid = false;

		if (index + 1 == i)
			return vec2(1, 0);
		else if (index - 1 == i)
			return vec2(-1, 0);
		else if (index + ph->size == i)
			return vec2(0, 1);

		return vec2(0, -1);
	}

	invalid = true;
	return DIR[0];
}

AI_normal::~AI_normal()
{
	delete ph;
}