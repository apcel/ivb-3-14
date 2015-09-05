#include "Button.hpp"

Button::~Button()
{
}

Button::Button() : Control()
{
	onMouseDown += {reinterpret_cast<IDelegate*>(this), static_cast<void(IDelegate::*)(Control *)>(&Button::OnMouseDown)};
	onMouseUp += {reinterpret_cast<IDelegate*>(this), static_cast<void(IDelegate::*)(Control *)>(&Button::OnMouseUp)};
	onMouseLeave += {reinterpret_cast<IDelegate*>(this), static_cast<void(IDelegate::*)(Control *)>(&Button::OnMouseLeave)};
	onMouseEnter += {reinterpret_cast<IDelegate*>(this), static_cast<void(IDelegate::*)(Control *)>(&Button::OnMouseEnter)};
	state_normal = nullptr;
	state_mouse = nullptr;
	state_down = nullptr;
}

void
Button::OnMouseDown(Control * sender)
{
	mouse_down = true;
	SetActiveState(state_down);
}

void
Button::OnMouseUp(Control * sender)
{
	if ( mouse_down) {
		onMouseClick(this);
		mouse_down = false;
		SetActiveState(state_mouse);
	}
}

void
Button::OnMouseEnter(Control * sender)
{
	SetActiveState(state_mouse);
}

void
Button::OnMouseLeave(Control * sender)
{
	SetActiveState(state_normal);
	mouse_down = false;
}

void
Button::SetActiveState(Control * active)
{
	if (state_normal != nullptr)
		state_normal->visible = false;
	if (state_mouse != nullptr)
		state_mouse->visible = false;
	if (state_down != nullptr)
		state_down->visible = false;

	if (active != nullptr)
		active->visible = true;
}