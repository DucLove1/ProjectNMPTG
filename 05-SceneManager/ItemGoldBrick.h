#pragma once
#include "GoldBrick.h"
#define RED_MUSHROOM 1
#define GREEN_MUSHROOM 2
#define LEAF 3
class ItemGoldBrick: public GoldBrick
{
private:
	CGameObject* item;
	int itemId;
	public:
	ItemGoldBrick(float x, float y, int item = 1) : GoldBrick(x, y)
	{
		this->item = NULL;
		this->itemId = item;
	}
	void InitializeRedMushroom(LPCOLLISIONEVENT e);
	void InitializeLeaf(LPCOLLISIONEVENT e);
	void GotHit(LPCOLLISIONEVENT e);
	void Render();
};

