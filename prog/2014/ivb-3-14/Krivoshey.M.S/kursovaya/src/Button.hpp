#include "hendel.h"

#ifndef __btn
	#define __btn
	class Button : public Control
	{
		bool mouse_down;

		void OnMouseDown(Control * sender);
		void OnMouseUp(Control * sender);
		void OnMouseEnter(Control * sender);
		void OnMouseLeave(Control * sender);

		void SetActiveState(Control * active);
	public:
		Control * state_normal;
		Control * state_mouse;
		Control * state_down;
		Delegate<Control> onMouseClick;

		Button();
		~Button();
	};
#endif