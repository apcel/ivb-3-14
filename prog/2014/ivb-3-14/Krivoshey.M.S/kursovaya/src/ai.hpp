#include "hendel.h"

#ifndef __ai
	#define __ai
	struct ai_node
	{
		bool up = false;
		bool down = false;
		bool right = false;
		bool left = false;

		bool isEnableDir(vec2 dir);
		char toChar();
		int weight();

		ai_node(){};
		ai_node(char c);
		ai_node(bool up, bool down, bool right, bool left) : up(up), down(down), right(right), left(left){};
	};

	class PathManager
	{
		int size2;
		bool* map;
		int* map_wave;

		void bind(int index, std::queue<int> * array, int level);
	public:
		int size;
		queue<int> get(int index_start, int index_end);

		PathManager(bool * map, int size);
		~PathManager();
	};

	class AI
	{
	public:
		static vec2 DIR[4];
		virtual vec2 operator()(int index, vec2 pos, vec2 old_dir) = 0;
	};

	class AI_simple : public AI
	{
		ai_node* aimap;
	public:
		AI_simple(ai_node* aimap);
		vec2 operator()(int index, vec2 pos, vec2 old_dir);
	};

	class AI_normal : public AI
	{
		queue<int> history;
		bool invalid;
		bool enrage;
		ai_node* aimap;
		PathManager* ph;
	public:
		int logic_type;
		struct{ int index; vec2 dir; bool enrage; }player_information;

		~AI_normal();
		AI_normal(ai_node* aimap, int size, int mode = 0);
		vec2 operator()(int index, vec2 pos, vec2 old_dir);
	};
#endif