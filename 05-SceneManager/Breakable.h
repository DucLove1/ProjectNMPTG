#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "debug.h"
#include "AssetIDs.h"

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CBreakable : public CGameObject
{
protected: 

	//BOOLEAN isBroken;
	//BOOLEAN isActivated;

public:

	CBreakable(float x, float y) : CGameObject(x, y)
	{
		this->x = x;
		this->y = y;
	}
	virtual void Render() = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;
	virtual void OnNoCollision(DWORD dt) = 0;
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) = 0;
	virtual int IsBlocking() { return 1; }

};

