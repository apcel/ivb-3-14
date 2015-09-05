#include "hendel.h"

#ifndef __unit
	#define __unit
	#define UNIT_ANIM_SPEED 0.03f
	#define RESPAWN_TIME 12.0f

	class GameObject : public Control
	{
	public:
		int specal;
		vec2 spawn;
		vec2 position;
		GameObject(vec2 position, string texture, Control * base);
	};

	class Unit : public GameObject
	{
		int uv_step = 0;
		vec2 memory;
		vec2 coord;
		int index;
		float anim_poll = 0;
		float respawn_pool;
		GLuint * unit_uv;
		float anim_count = 0;
	public:
		vec2 dir;
		AI* ai;
		float speed = 5.0f;
		bool vRotate_enable = true;
		bool idle;
		bool active = true;

		static int MAP_SIZE;
		static ai_node* aimap;

		Unit(vec2 position, string texture, Control * base, int anim_steap);
		Unit(vec2 position, string texture, Control * base);
		~Unit();

		void Rotate(vec2 dir);
		void OnTick(float delta);
		bool isFreeDir(vec2 dir);
		void teleport(vec2 nPos);
		void respawn();
		void doRespawn(float time);
		void die();
		void updateAI();
		vec2 getCordinate();
		int getIndex();

		static void Init(int MAP_SIZE);
	};
#endif