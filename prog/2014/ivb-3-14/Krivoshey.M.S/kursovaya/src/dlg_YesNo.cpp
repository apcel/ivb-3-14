#include "dlg_YesNo.hpp"

dlg_YesNo::dlg_YesNo(char * text, IDelegate* sender, void(IDelegate::* onClose)(Control *))
{
	this->sender = Control::loadFromFile("Data\\gui\\dlg_yesno.gui");
	Attach(this->sender);

	BindButton("yes", "Да", static_cast<void(IDelegate::*)(Control *)>(&dlg_YesNo::onYes));
	BindButton("no", "Нет", static_cast<void(IDelegate::*)(Control *)>(&dlg_YesNo::onNo));
	((Laber*)this->sender->getByNameFirst(btn_mask))->setText(text);

	onDestroy += {sender, onClose};
}

void
dlg_YesNo::onYes(Control * sender)
{
	result = true;
	die();
}

void
dlg_YesNo::onNo(Control * sender)
{
	result = false;
	die();
}