#include "GoldBrickWithButton.h"
#include "Button.h"
#include "PlayScene.h"
void GoldBrickWithButton::GotHit(LPCOLLISIONEVENT e)
{
	if (!this->active)
		return;
	button->IsAppear();
	this->active = false;
}
