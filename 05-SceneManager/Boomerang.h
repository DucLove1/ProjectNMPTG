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
	bool isActive;
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
	Boomerang(float x, float y, int nx)
		:CGameObject(x, y)
	{
		this->SetState(IS_HOLDED);
		timer = 0;
		prePosX = 0;
		prePosY = 0;
		stage = 0;
		timer = GameClock::GetInstance()->GetTime();
		vx = VX * nx;
		vy = -VY;
		isActive = true;
		this->nx = nx;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) override;
	void Render() override;
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt) override
	{
		x += vx * dt;
		y += vy * dt;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) override;
	void Throw();
	void Hold(float x, float y);
	void InActivate() { isActive = false; };
	bool IsRenderWhenPaused() { return false; }
	bool IsPauseRenderWhenTransform() { return false; }
	bool IsOnCamera();
};

