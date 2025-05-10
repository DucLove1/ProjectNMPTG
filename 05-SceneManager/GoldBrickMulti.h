#pragma once
#include "GoldBrick.h"
#define STATE_IDLE 0
#define STATE_GO_UP 1
#define STATE_GO_DOWN 2
#define SPEED_Y 0.1f
class GoldBrickMulti: public GoldBrick
{
private:
	int times;
	float maxY;
	float minY;
	void GoUp(DWORD dt);
	void GoDown(DWORD dt);
	public:
	GoldBrickMulti(float x, float y, int times = 5) : GoldBrick(x, y)
	{
		this->times = times;
		this->maxY = y;
		this->minY = y - GOLD_BRICK_BBOX_HEIGHT / 2;
	}
	void GotHit(LPCOLLISIONEVENT e);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

