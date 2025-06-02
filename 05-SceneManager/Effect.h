#pragma once
#include "GameObject.h"
#include "GameClock.h"
#define TIME_DISAPPEAR 2000
#define EFFECT_100 100
#define EFFECT_200 200
#define EFFECT_400 400
#define EFFECT_800 800
#define EFFECT_1000 1000
#define EFFECT_2000 2000
#define EFFECT_4000 4000
#define EFFECT_8000 8000
#define EFFECT_1UP 10000
#define EFFECT_TAIL_ATTACK 101
#define EFFECT_DISAPPEAR 102
#define VY -0.01f
class Effect : public CGameObject
{
private:
	int type;
	ULONGLONG timer;
public:
	Effect(float x, float y, int type) : CGameObject(x, y)
	{
		this->x = x;
		this->y = y;
		this->type = type;
		this->vy = (type != EFFECT_TAIL_ATTACK && type != EFFECT_DISAPPEAR) ? VY : 0;
		timer = GameClock::GetInstance()->GetTime();
	}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	bool IsUpdateWhenMarioTransform() override { return true; }
};

