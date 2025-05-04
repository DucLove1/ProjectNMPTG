#include "GoldBrick.h"
#include "AssetIDs.h"
#include "Animations.h"

void GoldBrick::Render()
{
	int aniId = ID_ANI_GOLD_BRICK_ACTIVE;
	if (active == false)
		aniId = ID_ANI_GOLD_BRICK_INACTIVE;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void GoldBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GOLD_BRICK_BBOX_WIDTH / 2;
	t = y - GOLD_BRICK_BBOX_HEIGHT / 2;
	r = l + GOLD_BRICK_BBOX_WIDTH;
	b = t + GOLD_BRICK_BBOX_HEIGHT;
}
