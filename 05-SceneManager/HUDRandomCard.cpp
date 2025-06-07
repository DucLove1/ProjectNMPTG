#include "HUDRandomCard.h"
#include "GameManager.h"
#include "AssetIDs.h"
void HUDRandomCard::Render()
{
	int item = GameManager::GetInstance()->GetCard(pos);
	int idSprite = ID_SPRITE_HUD_RANDOM_CARD_NONE;
	if (item == MUSHROOM_CARD_ID)
		idSprite = ID_SPRITE_HUD_RANDOM_CARD_MUSHROOM;
	else if (item == FIRE_FLOWER_CARD_ID)
		idSprite = ID_SPRITE_HUD_RANDOM_CARD_FIRE_FLOWER;
	else if (item == STAR_CARD_ID)
		idSprite = ID_SPRITE_HUD_RANDOM_CARD_STAR;
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	CSprites::GetInstance()->Get(idSprite)->Draw(cx + x, cy + y);
}
