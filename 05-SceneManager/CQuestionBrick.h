#pragma once
#include "Breakable.h"
#include "PlayScene.h"

#define EMPTY_ITEM 0
#define SPIN_STATE 1
#define COIN_ITEM 2
#define MUSHROOM_ITEM 3
#define LEAF_ITEM 4

#define CD_GOT_HIT 50

class CQuestionBrick : public CBreakable
{
protected:
	int timeCanHit;
	int typeOfHolder; // coin / mushrum / leaf
	float cdAnim;
	float cdHit;

public:
	CQuestionBrick(float x, float y, int typeOfHolder, int timeCanHit = 1) : CBreakable(x, y)
	{
		this->x = x;
		this->y = y;
		this->typeOfHolder = typeOfHolder;
		cdAnim = 0;
		cdHit = 0;
		this->timeCanHit = timeCanHit;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void GotHit(LPCOLLISIONEVENT e);
	int IsBlocking() { return 1; }

	int GetTypeOfHolder() { return this->typeOfHolder; }

};

