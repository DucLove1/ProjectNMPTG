#pragma once
#include "GameObject.h"
#define BULLET_SPEED 0.07f
#define BBOX_WIDTH 8
#define BBOX_HEIGHT 8
class VenusBullet : public CGameObject
{
private:
	float angle;
	float speed;
	int animId;
public:
	VenusBullet(float x, float y) : CGameObject(x, y)
	{
		this->speed = BULLET_SPEED;
		this->angle = -1;
		this->animId = -1;
	}
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
	void Fire(float x, float y, float angle);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnNoCollision(DWORD dt);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	bool IsRenderWhenPaused() { return false; }
	bool IsPauseRenderWhenTransform() { return false; }
};

