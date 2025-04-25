#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#define LEAF_BBOX_HEIGHT 14
#define LEAF_BBOX_WIDTH 16
#define LEAF_SPEED 0.05f

class CLeaf : public CGameObject
{
	float offSetLeftX;
	float offSetRightX;

	float firstForceHeight;
	BOOLEAN gotFirstForce;

public:
	CLeaf(float x, float y) : CGameObject(x, y)
	{
		offSetLeftX = x - LEAF_BBOX_WIDTH;
		offSetRightX = x + LEAF_BBOX_WIDTH;
		vy = LEAF_SPEED;
		firstForceHeight = y - LEAF_BBOX_HEIGHT*3;
		gotFirstForce = false;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnCollisionWith(LPCOLLISIONEVENT e) {};
	void OnNoCollision(DWORD dt) { x += vx * dt; y += vy * dt; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
};

