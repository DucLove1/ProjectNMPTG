#include "Mushroom.h"
#include "debug.h"
#include "RedMushroom.h"
#include "GreenMushroom.h"
#include "Effect.h"
#include "PlayScene.h"
void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if(!isActive)
		return;
	if (y <= offSetEnd)
	{
		wasGrowUp = true;
	}

	if (!wasGrowUp)
	{
		vy = -MUSHROOM_SPEED_Y;
		vx = 0;
	}
	else
	{
		ay = MUSHROOM_GRAVITY;
		if (nx >= 0)
			vx = MUSHROOM_SPEED_X;
		else
			vx = -MUSHROOM_SPEED_X;
	}
	vy += ay * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isActive)
	{
		l = x - MUSHROOM_BBOX_WIDTH / 2;
		t = y - MUSHROOM_BBOX_HEIGHT / 2;
		r = l + MUSHROOM_BBOX_WIDTH;
		b = t + MUSHROOM_BBOX_HEIGHT;
	}
	else
	{
		l = t = r = b = 0;
	}
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
	if (!e->obj->IsBlocking())
		return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	if (e->nx != 0)
	{
		vx = -vx;
		nx = -nx;
	}
}

void CMushroom::GotHit(int nx)
{
	this->isActive = true;
	this->nx = nx;
}

