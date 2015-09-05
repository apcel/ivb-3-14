#include "hendel.h"

#ifndef __level_editor
	#define __level_editor
	class level_editor : public Window
	{
		int MAP_SIZE;
		int MAP_SIZE_2;
		string map_name;
		vector<CheckBox*> br;
		bool needSave;
		GLuint * border_uv;
		struct Slot
		{
			int id;
			Control * control;
		}*Map;

		int brash = -1;
		
		void updatePoint(int x, int y, int v);
		void updatePoint(int x, int y);
		bool enableBlock(int x, int y);
		bool enablePoint(int x, int y);
		void br_check(CheckBox::Key *key);
		void map_mouse(Control * sender);
		void show_ai(CheckBox::Key* key);
		void exit(Control * sender);
		void exit_save(Control * sender);
		bool isNormalMap();
	public:

		void save();
		level_editor(char * map);
	};
#endif