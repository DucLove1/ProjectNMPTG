#include "RandomCardSystem.h"
#include "RandomCard.h"
#include "PlayScene.h"
#include "Sprites.h"
#define ID_SPRITE_RANDOM_CARD_FRAME 730000
RandomCardSystem::RandomCardSystem(float x, float y)
	: CGameObject(x, y)
{
	RandomCard* randomCard = new RandomCard(x, y);
	((LPPLAYSCENE)(CGame::GetInstance()->GetCurrentScene()))->AddObject(randomCard);
}

void RandomCardSystem::Render()
{
	CSprites::GetInstance()->Get(ID_SPRITE_RANDOM_CARD_FRAME)->Draw(x, y);
}
