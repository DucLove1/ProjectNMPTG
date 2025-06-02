#include "RandomCardEffect.h"
#include "Animations.h"
#define ID_ANI_EFFECT_MUSHROOM 72001
#define ID_ANI_EFFECT_FIRE_FLOWER 72002
#define ID_ANI_EFFECT_STAR 72003
#define TIME_TO_LIVE 1000 // milliseconds
void RandomCardEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l=t=r=b=0;
}
void RandomCardEffect::Render()
{
	int aniID = -1;
	switch (cardID)
	{
	case MUSHROOM_CARD_ID:
		aniID = ID_ANI_EFFECT_MUSHROOM;
		break;
	case FIRE_FLOWER_CARD_ID:
		aniID = ID_ANI_EFFECT_FIRE_FLOWER;
		break;
	case STAR_CARD_ID:
		aniID = ID_ANI_EFFECT_STAR;
		break;
	default:
		return; // Invalid card ID
	}
	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
}

void RandomCardEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if(GameClock::GetInstance()->GetTime() - timer > TIME_TO_LIVE)
	{
		this->Delete();
		return;
	}
	y += vy * dt; // Update vertical position if needed
}
