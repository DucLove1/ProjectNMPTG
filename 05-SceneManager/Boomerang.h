#pragma once
#include "GameObject.h"
#include "GameClock.h"
#define VX 0.11f
#define VY 0.025f
class Boomerang : public CGameObject
{
private:
	int stage;
	float prePosX;
	float prePosY;
	ULONGLONG timer;
	void UpdateStage1(DWORD dt);
	void UpdateStage2(DWORD dt);
	void UpdateStage3(DWORD dt);
	int GetStage();
public:
	enum
	{
		IS_HOLDED = 0,
		IS_THROWED = 1
	};
	Boomerang(float x, float y)
		:CGameObject(x, y)
	{
		this->SetState(IS_HOLDED);
		timer = 0;
		prePosX = 0;
		prePosY = 0;
		stage = 0;
		timer = GameClock::GetInstance()->GetTime();
		vx = VX;
		vy = -VY;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) override;
	void Render() override;
	int IsCollidable() { return 0; }
	void OnNoCollision(DWORD dt) override
	{
		x += vx * dt;
		y += vy * dt;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) override
	{
		l = t = r = b = 0;
	}
};

