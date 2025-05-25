#include "Effect.h"
#include "AssetIDs.h"
#include "Animations.h"
void Effect::Render()
{
	// render when effect is tail attack
	if (type == EFFECT_TAIL_ATTACK)
	{
		CAnimations::GetInstance()->Get(ID_ANI_TAIL_ATTACK_EFFECT)->Render(x, y);
		//CSprites::GetInstance()->Get(590012)->Draw(x, y);
		return;
	}
	// render when effect is disappear
	if (type == EFFECT_DISAPPEAR)
	{
		CAnimations::GetInstance()->Get(ID_ANI_DISAPPEAR_EFFECT)->Render(x, y);
		//CSprites::GetInstance()->Get(590012)->Draw(x, y);
		return;
	}
	// render when touch item
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
		// tail attack effect
		if (type == EFFECT_TAIL_ATTACK)
		{
			// if animation is done, delete the effect
			if (CAnimations::GetInstance()->Get(ID_ANI_TAIL_ATTACK_EFFECT)->Done())
			{
				// reset the animation
				CAnimations::GetInstance()->Get(ID_ANI_TAIL_ATTACK_EFFECT)->Reset();
				Delete();
				return;
			}
		}
		// disappear effect
		if (type == EFFECT_DISAPPEAR)
		{
			// if animation is done, delete the effect
			if (CAnimations::GetInstance()->Get(ID_ANI_DISAPPEAR_EFFECT)->Done())
			{
				// reset the animation
				CAnimations::GetInstance()->Get(ID_ANI_DISAPPEAR_EFFECT)->Reset();
				Delete();
				return;
			}
		}
		// effect touch item
		if (GameClock::GetInstance()->GetTime() - timer > TIME_DISAPPEAR)
		{
			Delete();
			return;
		}
	}

