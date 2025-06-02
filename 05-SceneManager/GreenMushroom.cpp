#include "GreenMushroom.h"
#include "Effect.h"
#include "PlayScene.h"
#define ID_GREEN_MUSHROOM 220001
void GreenMushroom::Render()
{
	if(isActive)
	CSprites::GetInstance()->Get(ID_GREEN_MUSHROOM)->Draw(x, y);
}

void GreenMushroom::Touched()
{
	Effect* effect = new Effect(x, y - 16, EFFECT_1UP);;
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(effect);
	GameManager::GetInstance()->AddLives(1);
	this->Delete();
}
