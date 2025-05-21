//class CMario;

#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
//#include "Mario.h"
#include "debug.h"

#define ATTACK_ROUND_TIME 500 // time to attack

#define TAIL_BBOX_WIDTH  14
#define TAIL_BBOX_HEIGHT 6


class CMarioTail : public CGameObject
{
	LPGAMEOBJECT player;
	bool isActive;
	int Mnx;
	bool isWhiping;
	float offSetLeft; //max range when attack
	float offSetRight;
	//float stayPositionX; // position when not attack
	//float stayPositionY;
	float atkVelocityX;
	float atkVelocityY;

	float fdt;
	ULONGLONG startAttack; //when it set, nothing can change

public:
	CMarioTail() :CGameObject(x, y)
	{

		Mnx = 0;
		vx = vy = atkVelocityX = atkVelocityY = 0;

		offSetLeft = x - TAIL_BBOX_WIDTH / 2;
		offSetRight = x + TAIL_BBOX_WIDTH / 2;

		isWhiping = false;
		isActive = true;


		fdt = 0.0f;
		startAttack = 0;
	}
	~CMarioTail() {};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void SetActive(bool value) { isActive = value; };
	void SetWhiping(bool value) { isWhiping = value; }
	bool IsWhiping() { return isWhiping; }

	void FollowPlayer(DWORD dt); // set Velocity base
	void TailAttack(DWORD dt); // set Velocity atk
	void UpdateMNx();
	void Modify(float& modifyX, float& modifyY);

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
};

