#include "BouncingCoin.h"

void CBouncingCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (wasReachToHeightBrace)
	{
		vy = FORCE;
	}

	y += vy * dt;
	if (y <= brace)
	{
		wasReachToHeightBrace = true;
	}
	if (y > begin)
	{
		this->Delete();
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBouncingCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(23001/*ID_ANI_BOUNCING_COIN*/)->Render(x, y);
}