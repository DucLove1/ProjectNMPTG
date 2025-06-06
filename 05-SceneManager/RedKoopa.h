#pragma once
#include "Koopa.h"
#include "Game.h"
#include "PlayScene.h"
#include "GameClock.h"
using namespace std;
class RedKoopa : public Koopa
{
private:
	ULONGLONG timerWing;
public:
	RedKoopa(float x, float y, int state) : Koopa(x, y, RED_KOOPA, state)
	{
		timerWing = GameClock::GetInstance()->GetTime();
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void UpdateStateHasWing();
	void UpdateStateHasNoWing();
	int GetDirection() { return nx; }
	void ChangeDirection()
	{
		nx = -nx;
		vx = -vx;
	}
	bool IsOnGround()
	{
		return onGround;
	}
};

