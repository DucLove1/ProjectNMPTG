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
	int stage = GetStage();
	DebugOut(L"stage %d\n", stage);
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
	// mac dinh la boomerang dang duoc cam
	int aniId = ID_ANI_BOOMERANG_SPIN;
	if (state == IS_THROWED)
	{
		aniId = ID_ANI_BOOMERANG_SPIN;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}
