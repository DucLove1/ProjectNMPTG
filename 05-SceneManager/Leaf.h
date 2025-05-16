#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#define LEAF_BBOX_HEIGHT 14
#define LEAF_BBOX_WIDTH 16
#define LEAF_SPEED 0.05f
#define DISTANCE_RISE 48

class CLeaf : public CGameObject
{
	float offSetLeftX;
	float offSetRightX;
	float firstForceHeight;
	BOOLEAN gotFirstForce;
	int preNx;
	//bool canRender;

public:
	CLeaf(float x, float y) : CGameObject(x, y)
	{
		offSetLeftX = x - LEAF_BBOX_WIDTH;
		offSetRightX = x + LEAF_BBOX_WIDTH;
		vy = LEAF_SPEED;
		firstForceHeight = y - DISTANCE_RISE;
		gotFirstForce = false;
		preNx = nx;
		//canRender = true;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnCollisionWith(LPCOLLISIONEVENT e) {};
	void OnNoCollision(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
};

