#ifndef ___setting
		#define ___setting
	class setting
	{
	public:
		static setting* instance;
		char * GAME_LEVEL;
		bool sse;
		bool anim_points;
		bool show_fps;
		bool debug_show_ai;
		setting();
	};
#endif