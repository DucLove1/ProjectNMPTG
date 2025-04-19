#include "Mushroom.h"


void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (y <= offSetEnd)
		wasGrowUp = true;

	if (!wasGrowUp)
	{
		vy = -MUSHROOM_SPEED;
		vx = 0;
	}
	else
	{
		vy = 0.0f; // temp
		if (nx >= 0)
			vx = MUSHROOM_SPEED;
		else
			vx = -MUSHROOM_SPEED;
	}
	y += vy * dt;
	x += vx * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_MUSHROOM)->Render(x, y);
	RenderBoundingBox();
}

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_BBOX_WIDTH / 2;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH;
	b = t + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	/*if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}*/
}