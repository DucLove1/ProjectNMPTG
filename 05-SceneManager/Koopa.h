#pragma once
#include "CEnemy.h"
#include "GameClock.h"
#define GREEN_KOOPA 0
#define RED_KOOPA 1
#define KOOPA_GRAVITY 0.003f
#define KOOPA_WALKING_SPEED 0.03f
#define KOOPA_JUMPING_FORCE 0.08f
#define KOOPA_IN_SHELL_SPEED 0.15f

#define KOOPA_SPRITE_HAS_WING_WIDTH 15.0f
#define KOOPA_SPRITE_HAS_WING_HEIGHT 27.0f
#define KOOPA_SPRITE_HAS_NO_WING_WIDTH 15.0f
#define KOOPA_SPRITE_HAS_NO_WING_HEIGHT 26.0f
#define KOOPA_SPRITE_IN_SHELL_WIDTH 15.0f
#define KOOPA_SPRITE_IN_SHELL_HEIGHT 15.0f

#define TIME_OUT_OF_SHELL 10000
class Koopa : public CEnemy
{
private:
	ULONGLONG timerInShell;
	int type;
	int lastAnimationId;
	ULONGLONG timerKnockOut;

	BOOLEAN isHolded;

	void SetStateHasWing();
	void SetStateHasNoWing();
	void SetStateInShellUp();
	void SetStateInShellDown();
	void SetStateKnockOut();
public:
	enum State
	{
		HAS_WING,
		HAS_NO_WING,
		IN_SHELL_UP,
		IN_SHELL_DOWN,
		KNOCK_OUT
	};
	Koopa(float x, float y, int type = RED_KOOPA, int state = HAS_WING)
		: CEnemy(x, y)
	{
		this->type = type;
		this->state = -1;
		SetState(state);
		this->ay = KOOPA_GRAVITY;
		this->ax = 0.0f;
		this->vx = KOOPA_WALKING_SPEED;
		this->onGround = false;
		timerInShell = 0;
		this->lastAnimationId = -1;
		isHolded = false;
	}
	void SetState(int state) override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void OnNoCollision(DWORD dt) override;
	void OnCollisionWith(LPCOLLISIONEVENT e) override;
	void OnCollisionWithEnemy(LPCOLLISIONEVENT e);
	//void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void UpdateStateInShell(DWORD dt);
	void UpdateStateKnockOut(DWORD dt);
	void Render() override;
	void KickedFromTop(CGameObject*);
	void MoveInShell(int direction);
	void KickedFromBottom(CGameObject*) {};
	void TouchTwoSide(CGameObject*) {};
	int IsCollidable() override { return state != KNOCK_OUT; }
	void KnockedOut(CGameObject*);
	bool IsAlive() { return state != KNOCK_OUT; }

	void ReleaseByPlayer(CMario* e);
	bool IsTimeOut() { return (GameClock::GetInstance()->GetTime() - timerInShell >= TIME_OUT_OF_SHELL); }
	void SetHolded(bool isHolded) { this->isHolded = isHolded; }
	bool IsHolded() { return isHolded; }

};
