#pragma once
#include "GoldBrick.h"
#define STATE_IDLE 0
#define STATE_GO_UP 1
#define STATE_GO_DOWN 2
#define SPEED_Y 0.1f
#define TIME_TO_OFF 2000
class GoldBrickMulti: public GoldBrick
{
private:
	float maxY;
	float minY;
	ULONGLONG timer;
	void GoUp(DWORD dt);
	void GoDown(DWORD dt);
	public:
	GoldBrickMulti(float x, float y) : GoldBrick(x, y)
	{
		this->timer = -1;
		this->maxY = y;
		this->minY = y - GOLD_BRICK_BBOX_HEIGHT / 2;
	}
	void GotHit(LPCOLLISIONEVENT e);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnNoCollision(DWORD dt);
	int IsCollidable() override { return this->active; }
};

