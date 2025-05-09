#include "VenusBullet.h"
#include "AssetIDs.h"
#include "Animations.h"
void VenusBullet::Fire(float x, float y, float angle)
{
	this->x = x;
	this->y = y;
	this->angle = angle;
}

void VenusBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->angle == -1)
		return;
	this->vx = cos(angle / 180.0f * 3.14) * speed;
	this->vy = sin(angle / 180.0f * 3.14) * speed;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void VenusBullet::OnNoCollision(DWORD dt)
{
	this->x += this->vx * dt;
	this->y += this->vy * dt;
}
void VenusBullet::Render()
{
	if(this->angle >= 90 && this->angle < 270)
	{
		this->animId = ID_ANI_BULLET_SPIN_LEFT;
	}
	else
	{
		this->animId = ID_ANI_BULLET_SPIN_RIGHT;
	}
	CAnimations::GetInstance()->Get(this->animId)->Render(this->x, this->y);
}

void VenusBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->x - BBOX_WIDTH / 2;
	t = this->y - BBOX_HEIGHT / 2;
	r = l + BBOX_WIDTH;
	b = t + BBOX_HEIGHT;
}
