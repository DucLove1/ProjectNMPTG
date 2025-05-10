#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#define BCOIN_BBOX_HEIGHT   16
#define BCOIN_BBOX_WIDTH   14

#define HEIGHT_BRACE BCOIN_BBOX_HEIGHT*3
#define FORCE 0.15f

class CBouncingCoin : public CGameObject
{
	float begin;
	float brace;
	bool wasReachToHeightBrace;
public:
	CBouncingCoin(float x, float y) : CGameObject(x, y)
	{
		begin = y;
		brace = begin - HEIGHT_BRACE;
		wasReachToHeightBrace = false;
		vx = vy = 0;
		vy = -FORCE;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnCollisionWith(LPCOLLISIONEVENT e) {};
	void OnNoCollision(DWORD dt) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - BCOIN_BBOX_WIDTH / 2;
		t = y - BCOIN_BBOX_HEIGHT / 2;
		r = l + BCOIN_BBOX_WIDTH;
		b = t + BCOIN_BBOX_HEIGHT;
	}
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
};
