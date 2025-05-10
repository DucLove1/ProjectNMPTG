#pragma once
#include "GameObject.h"
#define INACTIVE 0
#define ACTIVE 1
#define GOLD_BRICK_BBOX_WIDTH 16
#define GOLD_BRICK_BBOX_HEIGHT 16
class GoldBrick: public CGameObject
{
protected:
	bool active;
public:
	GoldBrick(float x, float y) : CGameObject(x, y)
	{
		this->x = x;
		this->y = y;
		this->active = true;
	}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 0; }
	virtual void GotHit(LPCOLLISIONEVENT e) = 0;

};

