#include "ParticalBreak.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "Collision.h"
int ParticalBreak::IsCollidable()
{
    return 0;
}

void ParticalBreak::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = 0;
	top = 0;
	right = 0;
	bottom = 0;
}

void ParticalBreak::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_PARTICAL_BREAK_BRICK)->Render(x, y);
}

void ParticalBreak::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx += ax * dt;
	vy += ay * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void ParticalBreak::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	if (GetTickCount64() - timer_delete > 1000)
	{
		Delete();
	}
}
