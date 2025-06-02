#pragma once
#include "GoldBrick.h"
#include "GreenMushroom.h"
#include "RedMushroom.h"
#include "PlayScene.h"
#define RED_MUSHROOM 1
#define GREEN_MUSHROOM 2
#define LEAF 3
#define RANDOM_ITEM 0
#define GREEN_MUSHROOM_ITEM 1
#define STATE_IDLE 0
#define STATE_GO_UP 1
#define STATE_GO_DOWN 2
#define VY 0.1f
class ItemGoldBrick : public GoldBrick
{
private:
	float maxY;
	float minY;
	CGameObject* item1;
	CGameObject* item2;
	bool wayChooseItem;
	bool doneHit;
	int ChooseItem();
	void GoUp(DWORD dt);
	void GoDown(DWORD dt);
public:
	ItemGoldBrick(float x, float y, bool wayChooseItem = 0) : GoldBrick(x, y)
	{
		this->wayChooseItem = wayChooseItem;
		if (wayChooseItem == GREEN_MUSHROOM_ITEM)
			item1 = new GreenMushroom(x, y, 1);
		else item1 = new RedMushroom(x, y, 1);
		((LPPLAYSCENE)(CGame::GetInstance()->GetCurrentScene()))->AddObject(item1);
		item2 = nullptr;
		maxY = y;
		minY = y - GOLD_BRICK_BBOX_HEIGHT / 2;
		vy = 0;
		doneHit = false;
	}
	//void InitializeRedMushroom(LPCOLLISIONEVENT e);
	//void InitializeGreenMushroom(LPCOLLISIONEVENT e);
	void InitializeLeaf(LPCOLLISIONEVENT e);
	void GotHit(LPCOLLISIONEVENT e);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	//void OnCollisionWith(LPCOLLISIONEVENT e) override;

	//void OnNoCollision(DWORD dt) override;

};

