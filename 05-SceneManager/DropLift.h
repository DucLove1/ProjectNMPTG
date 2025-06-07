class CMario;
#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Game.h"
#include "PlayScene.h"

#define GRAVITY 0.00025f
class DropLift : public CGameObject
{
private:
	bool isActive;
	bool isTouched;
	bool hasPlayer;

	CMario* player;


public:
	DropLift(float x, float y) : CGameObject(x, y)
	{
		this->isActive = false;
		this->isTouched = false;
		this->hasPlayer = false;
		this->vx = -0.02f;
		this->vy = 0;
	}
	int IsCollidable() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void Render() override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) override;
	int IsBlocking() override { return 1; }
	void Touch() { isTouched = true; }
	bool IsOnCamera();
	void OnNoCollision(DWORD dt) override;
	void OnCollisionWith(LPCOLLISIONEVENT e) override;

	void GotLinked();
	//void BreakLink() { player = nullptr; }

	void OnCollidedWithMario(LPCOLLISIONEVENT e);
};

