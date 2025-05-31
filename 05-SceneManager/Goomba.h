#pragma once
#include "CEnemy.h"
#include "Game.h"
#include "PlayScene.h"
#include "GameClock.h"
#define GOOMBA_GRAVITY 0.0015f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_JUMPING_FORCE 0.08f
#define GOOMBA_FLY_FORCE 0.3f

#define GOOMBA_ALIVE_BBOX_WIDTH 16.0f
#define GOOMBA_ALIVE_BBOX_HEIGHT 14.0f
#define GOOMBA_DIE_BBOX_WIDTH 16.0f
#define GOOMBA_DIE_BBOX_HEIGHT 9.0f

#define GOOMBA_SPRITE_WIDTH 16.0f
#define GOOMBA_SPRITE_HEIGHT 14.0f
#define GOOMBA_SPRITE_HEIGHT_WING 24.0f
#define GOOMBA_SPRITE_WIDTH_WING 20.0f
#define GOOMBA_SPRITE_HEIGHT_DIE 9.0f

#define GOOMBA_DIE_TIMEOUT 500

#define TIME_JUMPING 1500
#define TIME_FLYING 2000
#define TIME_KNOCK_OUT 200
#define TIME_OUT_KNOCK_OUT 5000
#define TIME_FOLLOW 20000
#define DISTANCE_FOLLOW 100
#define GOOMBA 0
#define RED_GOOMBA 1
class CGoomba : public CEnemy
{
private:
	CGameObject* mario;
	ULONGLONG timerFly;
	int type;
	ULONGLONG die_start;
	int countJump;
	ULONGLONG timerKnockOut;
	ULONGLONG timerFollow;
	void SetStateDie();
	void SetStateHasNoWing();
	void SetStateHasWing();
	void SetStateKockOut();
public:
	enum State
	{
		HAS_WING,
		HAS_NO_WING,
		DIE,
		KNOCK_OUT
	};
	CGoomba(float x, float y, int type = RED_GOOMBA, int state = HAS_WING) : CEnemy(x, y)
	{
		this->type = type;
		this->state = -1;
		SetState(state);
		this->ay = GOOMBA_GRAVITY;
		this->ax = 0;
		this->vx = -GOOMBA_WALKING_SPEED;
		this->onGround = false;
		timerFly = 0;
		countJump = 0;
		this->mario = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		this->timerFollow = GameClock::GetInstance()->GetTime();
	}
	void SetState(int state) override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void OnNoCollision(DWORD dt) override;
	void OnCollisionWith(LPCOLLISIONEVENT e) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void UpdateState();
	void Render() override;
	void KickedFromTop(CGameObject*) override;
	void KickedFromBottom(CGameObject*) override;
	void KnockedOut(CGameObject*);
	void TouchTwoSide(CGameObject*) {};
	int IsCollidable() override { return IsAlive(); }
	bool IsAlive() override { return state != DIE && state != KNOCK_OUT; };
};