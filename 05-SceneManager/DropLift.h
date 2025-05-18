#pragma once
#include "GameObject.h"
#define GRAVITY 0.0002f
class DropLift : public CGameObject
{
private:
	bool isActive;
	bool isTouched;
public:
	DropLift(float x, float y) : CGameObject(x, y)
	{
		this->isActive = false;
		this->isTouched = false;
		this->vx = -0.02f;
		this->vy = 0;
	}
	int IsCollidable() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void Render() override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) override;
	int IsBlocking() override { return 1; }
	void Touch() { isTouched = true; }
	//void OnNoCollision(DWORD dt) override;
};

