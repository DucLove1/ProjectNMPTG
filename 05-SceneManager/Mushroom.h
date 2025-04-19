#pragma once
#include "GameObject.h"
#include "AssetIDs.h"
#include "Animation.h"
#include "Animations.h"

#define MUSHROOM_BBOX_HEIGHT 16
#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_SPEED 0.05f

class CMushroom : public CGameObject
{
	float offSetBegin;
	float offSetEnd;

	BOOLEAN wasGrowUp;

public:
	CMushroom(float x, float y, int nx) : CGameObject(x, y) 
	{
		offSetBegin = this->y;
		offSetEnd = this->y - MUSHROOM_BBOX_HEIGHT -1;
		vx = MUSHROOM_SPEED;
		this->nx = nx;
		wasGrowUp = false;
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	int IsBlocking() { return 1; }
};

