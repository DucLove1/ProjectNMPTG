#include "GoldBrickWithButton.h"
#include "Button.h"
#include "PlayScene.h"
void GoldBrickWithButton::GotHit(LPCOLLISIONEVENT e)
{
	if (!this->active)
		return;
	CGameObject* button = new Button(this->x, this->y - 16, this->bricks);
	((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(button);
	this->active = false;
}
