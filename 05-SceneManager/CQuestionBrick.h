#pragma once
#include "Breakable.h"
#include "PlayScene.h"
#include "RedMushroom.h"
#define EMPTY_ITEM 0
#define SPIN_STATE 1
#define COIN_ITEM 2
#define MUSHROOM_ITEM 3
#define LEAF_ITEM 4

#define CD_GOT_HIT 50
#define STATE_GO_UP 1
#define STATE_GO_DOWN 2
#define STATE_IDLE 0
#define SPEED_Y 0.1f
class CQuestionBrick : public CBreakable
{
protected:
	int timeCanHit;
	int typeOfHolder; // coin / mushrum / leaf
	float cdAnim;
	float cdHit;
	CGameObject* item1;
	CGameObject* item2;
	float maxY, minY;
public:
	CQuestionBrick(float x, float y, int typeOfHolder, int timeCanHit = 1) : CBreakable(x, y)
	{
		this->x = x;
		this->y = y;
		this->typeOfHolder = typeOfHolder;
		cdAnim = 0;
		cdHit = 0;
		this->timeCanHit = timeCanHit;
		this->item1 = (typeOfHolder == COIN_ITEM) ? NULL : new RedMushroom(x,y,1);
		this->item2 = nullptr;
		if(item1)
		{
			dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene())->AddObject(item1);
		}
		this->maxY = y;
		this->minY = y - 8;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void GotHit(LPCOLLISIONEVENT e);
	int IsBlocking() { return 1; }

	int GetTypeOfHolder() { return this->typeOfHolder; }
	void GoUp(DWORD dt);
	void GoDown(DWORD dt);
};

