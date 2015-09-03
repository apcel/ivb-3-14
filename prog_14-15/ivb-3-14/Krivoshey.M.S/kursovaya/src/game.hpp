#include "hendel.h"

#ifndef __game_control
	#define __game_control
	#define BORDER_UV_COUNT 16
	#define PLAYER_SPEED 6.0f
	#define object_size 20
	#define BONUS_TIME 12.0f
	#define MAX_TICK_DELTA 0.01f

	class game : public Control
	{
		int MAP_SIZE;
		int MAP_SIZE_2;
		bool *key_old;
		float *point_a;
		ai_node *aimap;
		ai_node *aimap_pl;
		Control ** border;
		Control * sender;
		Control * game_plane;
		Control * border_plane;
		Control * background;
		Laber * score_text;
		Laber * bonus_text;
		Laber * bonus_t_text;
		Laber * live_text;
		GLuint * border_uv;
		GameObject ** gameobject;
		Unit * player;
		vector<Unit*> mobs;
		vec2 task;
		pause_menu* pause_m = nullptr;
		Particle::EmitterPoint* player_fx;
		vector<Particle::EmitterPoint*> mobs_fx;
		float bonus;
		int score = 0;
		int score_only = 0;
		int total_score = 0;
		int live = 3;

		void OnTick(float delta);
		void OnKeyDown(int key);
		bool enableBlock(int x, int y);
		void onPauseEnd(Control * menu);
		void end(bool vactory);
		void renderBackground();
		void updateFX(Particle::EmitterPoint* em, Unit * unit, bool enable);
		Particle::EmitterPoint* createFX(Control * sender, bool player);
	public:
		static bool pause;
		static int border_mask[16];

		game(char * level);

		void UpdateTransform(bool updateChildren);
		void Render();
	};
#endif