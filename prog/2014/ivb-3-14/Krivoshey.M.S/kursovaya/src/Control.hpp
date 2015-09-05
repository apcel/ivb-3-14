#include "hendel.h"

#ifndef __robj
	#define __robj
	#define alignment_leftORtop 0
	#define alignment_center 1
	#define alignment_rightRObuttom 2
	#define mouse_button_reg 5

	class Control : public IDelegate
	{
	protected:
		mat3 MVP;
		scaleValue pos;
		scaleValue scale;
		scaleValue rot;
		float angine;
		vec4 bound;
		bool isMouseEnter;
		int align_h = 0;
		int align_v = 0;

		static bool invertYRender;
		static map<string, Control*> cache;
		static Control * loadFromLines(char ** data, int offest, int len);

		vec2 getOffestPos(int type);

	public:
		vector<Control*> controls;
		shader * sh;
		GLuint uvbuffer;
		GLuint texture;
		Control * base;
		vec4 backColor;
		vec4 colorMult;
		bool visible = true;
		bool _rendable = true;
		bool needDestroy = false;
		string name;
		Delegate<Control> onMouseEnter;
		Delegate<Control> onMouseLeave;
		Delegate<Control> onMouseDown;
		Delegate<Control> onMouseUp;
		Delegate<Control> onDestroy;

		static bool mouse_btn_state[mouse_button_reg];
		static bool mouse_btn_state_old[mouse_button_reg];
		static bool key_state[KEY_REG];
		static vec2 mouse_pos;
		static vec2 mouse_pos_old;
		static shader* Default_shader;
		static vec2 ScreenSize;
		static float tickDelta;
		static GLuint default_uv;
		static GLuint default_vx;
		static int renderCount;

		Control(string Texture, GLuint uv);
		Control(string Texture);
		Control();
		~Control();

		virtual void Render();
		virtual void Move(scaleValue point);
		virtual void Scale(scaleValue transform);
		virtual void Rotate(float angine);
		virtual void Transform(scaleValue position, scaleValue scale);
		virtual void Transform(scaleValue position, scaleValue scale, float angine);
		virtual void UpdateTransform(bool updateChildren = true);
		virtual void Attach(Control *control);
		virtual void Detach(Control *control, bool destroy = true);
		virtual void DetachAll(bool destroy = true);
		void MoveToTop();
		void MoveToBack();
		virtual Control * Clone();
		vector<Control*> getByName(string name);
		Control* getByNameFirst(string name);

		vec2 getAlign();
		void setAlign(int horizontal, int vertical);
		void setAlign(vec2 value);
		vec4 getBound(int type);
		vec2 getPos(int type);
		vec2 getScale(int type);
		scaleValue getPosition();
		void die();
		void cleaner();
		GLuint renderToTexture();
		void renderToTexture(GLuint id);

		static vec2 pixelToScreen(vec2 pos);
		static vec2 screenToPixel(vec2 pos);
		static void Init();
		static Control * loadFromFile(string name);
	};
#endif