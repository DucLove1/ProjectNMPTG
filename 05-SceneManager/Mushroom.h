#pragma once
#include "GameObject.h"
#include "AssetIDs.h"
#include "Animation.h"
#include "Animations.h"

#define MUSHROOM_BBOX_HEIGHT 16
#define MUSHROOM_BBOX_WIDTH 15
#define MUSHROOM_SPEED_Y 0.02f
#define MUSHROOM_SPEED_X 0.05f
#define MUSHROOM_GRAVITY 0.001f
class CMushroom : public CGameObject
{
	float offSetBegin;
	float offSetEnd;
	float ay;
	BOOLEAN wasGrowUp;
protected: 
	bool isActive;

public:
	CMushroom(float x, float y, int nx) : CGameObject(x, y) 
	{
		offSetBegin = this->y;
		offSetEnd = this->y - MUSHROOM_BBOX_HEIGHT;
		vx = MUSHROOM_SPEED_X;
		this->nx = nx;
		wasGrowUp = false;
		this->ay = 0;
		this->isActive = false;
	}

	void Render() = 0;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	void GotHit(int nx);
};

