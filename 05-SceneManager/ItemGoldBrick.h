#pragma once
#include "GoldBrick.h"
#define RED_MUSHROOM 1
#define GREEN_MUSHROOM 2
#define LEAF 3
#define RANDOM_ITEM 0
#define GREEN_MUSHROOM_ITEM 1
class ItemGoldBrick : public GoldBrick
{
private:
	CGameObject* item;
	bool wayChooseItem;
	int ChooseItem();
public:
	ItemGoldBrick(float x, float y, bool wayChooseItem = 0) : GoldBrick(x, y)
	{
		this->item = NULL;
		this->wayChooseItem = wayChooseItem;
	}
	void InitializeRedMushroom(LPCOLLISIONEVENT e);
	void InitializeGreenMushroom(LPCOLLISIONEVENT e);
	void InitializeLeaf(LPCOLLISIONEVENT e);
	void GotHit(LPCOLLISIONEVENT e);
	void Render();
};

