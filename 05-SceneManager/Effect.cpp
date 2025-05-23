#include "Effect.h"
#include "AssetIDs.h"
void Effect::Render()
{
	int spriteId = 0;
	switch (type)
	{
	case EFFECT_100:
		spriteId = ID_SPRITE_EFFECT_100;
		break;
	case EFFECT_200:
		spriteId = ID_SPRITE_EFFECT_200;
		break;
	case EFFECT_400:
		spriteId = ID_SPRITE_EFFECT_400;
		break;
	case EFFECT_800:
		spriteId = ID_SPRITE_EFFECT_800;
		break;
	case EFFECT_1000:
		spriteId = ID_SPRITE_EFFECT_1000;
		break;
	case EFFECT_2000:
		spriteId = ID_SPRITE_EFFECT_2000;
		break;
	case EFFECT_4000:
		spriteId = ID_SPRITE_EFFECT_4000;
		break;
	case EFFECT_8000:
		spriteId = ID_SPRITE_EFFECT_8000;
		break;
	case EFFECT_1UP:
		spriteId = ID_SPRITE_EFFECT_1UP;
		break;
	}
	// Render the effect sprite
	CSprites::GetInstance()->Get(spriteId)->Draw(x, y);
}

	void Effect::Update(DWORD dt, vector<LPGAMEOBJECT>*coObjects)
	{
		y += vy * dt;
		if (GameClock::GetInstance()->GetTime() - timer > TIME_DISAPPEAR)
		{
			Delete();
			return;
		}
	}

