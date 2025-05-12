#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "Mario.h"
#include "debug.h"

#define TAIL_BBOX_WIDTH  14
#define TAIL_BBOX_HEIGHT 6


class CMarioTail : public CGameObject
{
	LPGAMEOBJECT player;
	bool isActive;
	int Mnx;
	bool isWhiping;
	bool isHalfWhiping; // when player got half whiping, tail will move to other side and stop
	float offSetLeft; //max range when attack
	float offSetRight;
	//float stayPositionX; // position when not attack
	//float stayPositionY;
	float atkVelocityX;
	float atkVelocityY;

public:
	CMarioTail() :CGameObject(x, y)
	{

		Mnx = 0;
		vx = vy = atkVelocityX = atkVelocityY = 0;

		offSetLeft = x - TAIL_BBOX_WIDTH / 2;
		offSetRight = x + TAIL_BBOX_WIDTH / 2;
	}
	~CMarioTail() {};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void SetActive(bool value) { isActive = value; };

	void FollowPlayer(DWORD dt); // set Velocity base
	void CalTailAttack(int Mnx, DWORD dt); // set Velocity atk
	void UpdateMNx();
	void Modify(float& modifyX, float& modifyY);

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
};

