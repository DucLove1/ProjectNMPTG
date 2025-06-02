#include "RedMushroom.h"
#include "Effect.h"
#include "PlayScene.h"
void RedMushroom::Touched()
{
	Effect* effect = new Effect(x, y - 16, EFFECT_1000);
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(effect);
	GameManager::GetInstance()->AddScore(1000);
	this->Delete();
}
