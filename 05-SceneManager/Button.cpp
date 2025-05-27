#include "Button.h"
#include "AssetIDs.h"
#include "GoldBrickWithButton.h"
#include "Animations.h"
#define BUTTON_WIDTH 14
#define BUTTON_HEIGHT 14
#define BUTTON_HEIGHT_PRESSED 6
void Button::Render()
{
	if(state == BUTTON_STATE_PRESSED)
	{
		// Render the button in pressed state
		CSprites::GetInstance()->Get(ID_SPRITE_BUTTON_PRESSED)->Draw(x, y);
	}
	else
	{
		// Render the button in normal state
		CAnimations::GetInstance()->Get(ID_ANI_BUTTON_NORMAL)->Render(x, y);
	}
}

void Button::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if(this->state == BUTTON_STATE_PRESSED || this->state == BUTTON_STATE_NOT_PRESSED)
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
	else
	{
		l = x - BUTTON_WIDTH / 2;
		t = y - BUTTON_HEIGHT / 2;
		r = l + BUTTON_WIDTH;
		b = t + BUTTON_HEIGHT;
	}
}

void Button::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BUTTON_STATE_PRESSED:
		y += (BUTTON_HEIGHT - BUTTON_HEIGHT_PRESSED) / 2;
		break;
	case BUTTON_STATE_NORMAL:
		break;
	default:
		break;
	}
}

void Button::GetPress()
{
	if(state == BUTTON_STATE_PRESSED)
		return;
	SetState(BUTTON_STATE_PRESSED);
}

void Button::IsAppear()
{
	SetState(BUTTON_STATE_NORMAL);
	this->y -= 16;
}
