#include "hendel.h"

#ifndef __dlg_yesno
	#define __dlg_yesno
	class dlg_YesNo : public Window
	{
		Delegate<Control> onClose;

		void onYes(Control * sender);
		void onNo(Control * sender);
	public:
		bool result;

		dlg_YesNo(char * text, IDelegate* sender, void(IDelegate::* onClose)(Control *));
	};
#endif