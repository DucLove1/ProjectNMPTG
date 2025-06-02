#include "RandomCard.h"
#include "Animations.h"
#include "RandomCardEffect.h"
#include "PlayScene.h"
#define ID_ANI_RANDOM_CARD 72000
#define ID_SPRITE_NON_CARD 720004
void RandomCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if(state == INACTIVE)
	{
		l = t = r = b = 0;
		return;
	}
	l = x - WIDTH / 2;
	t = y - HEIGHT / 2;
	r = l + WIDTH;
	b = t + HEIGHT;
}

void RandomCard::Render()
{
	if (state == INACTIVE)
	{
		CSprites::GetInstance()->Get(ID_SPRITE_NON_CARD)->Draw(x, y);
	}
	else
	CAnimations::GetInstance()->Get(ID_ANI_RANDOM_CARD)->Render(x, y);
}

void RandomCard::Touched()
{
	state = INACTIVE;
	int curItem = CAnimations::GetInstance()->Get(ID_ANI_RANDOM_CARD)->GetCurrentFrame();
	// make animation item here
	RandomCardEffect* effect = new RandomCardEffect(x, y, curItem);
	((LPPLAYSCENE)(CGame::GetInstance()->GetCurrentScene()))->AddObject(effect);
}

