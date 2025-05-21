#include "Boomerang.h"
#include "AssetIDs.h"
#include "Animations.h"

#define MAX_HEIGHT 50
#define MAX_WIDTH 100
#define TIME_BOOMERANG_MOVE 4000
#define TIME_FOR_STAGE_1 1000
#define TIME_FOR_STAGE_2 2000
#define TIME_FOR_STAGE_3 1000
#define PI 3.14
#define BBOX_WIDTH 16
#define BBOX_HEIGHT 16
void Boomerang::UpdateStage1(DWORD dt)
{
	/*float progress = (float)(GameClock::GetInstance()->GetTime() - timer) / TIME_FOR_STAGE_1;
	vy = -0.02 * (1 - progress);*/
	if (vy < 0)
		vy += 0.0000015f;
	else vy = 0;
}
void Boomerang::UpdateStage2(DWORD dt)
{
	float progress = (float)(GameClock::GetInstance()->GetTime() - timer - TIME_FOR_STAGE_1) / TIME_BOOMERANG_MOVE;
	double angle = 2*PI * progress;
	vx = VX * cos(angle);
	vy = VY * sin(angle);
}
void Boomerang::UpdateStage3(DWORD dt)
{
	vx = -abs(vx);
	vy = 0;
}
int Boomerang::GetStage()
{
	//return 1;
	ULONGLONG currentTime = GameClock::GetInstance()->GetTime();
	ULONGLONG time = currentTime - timer;
	if (time < TIME_FOR_STAGE_1)
	{
		return 1;
	}
	else if (time < TIME_FOR_STAGE_1 + TIME_FOR_STAGE_2)
	{
		return 2;
	}
	return 3;
}
void Boomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == IS_HOLDED || !isActive)
		return;
	int stage = GetStage();
	switch (stage)
	{
	case 1:
		UpdateStage1(dt);
		break;
	case 2:
		UpdateStage2(dt);
		break;
	case 3:
		UpdateStage3(dt);
		break;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void Boomerang::Render()
{
	if (!isActive)
		return;
	// mac dinh la boomerang dang duoc cam
	int aniId = ID_ANI_BOOMERANG_HOLD;
	if (state == IS_THROWED)
	{
		aniId = ID_ANI_BOOMERANG_SPIN;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void Boomerang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (!isActive)
	{
		l = t = r = b = 0;
		return;
	}
	l = x - BBOX_WIDTH / 2;
	t = y - BBOX_HEIGHT / 2;
	r = l + BBOX_WIDTH;
	b = t + BBOX_HEIGHT;
}

void Boomerang::Throw()
{
	isActive == true;
	SetState(IS_THROWED);
}

void Boomerang::Hold(float x, float y)
{
	isActive = true;
	SetState(IS_HOLDED);
	this->x = x;
	this->y = y;
}
