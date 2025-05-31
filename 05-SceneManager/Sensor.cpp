#include "Sensor.h"
#include "RedKoopa.h"
#include "Collision.h"
void Sensor::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - SENSOR_BBOX_WIDTH / 2;
	top = y - SENSOR_BBOX_HEIGHT / 2;
	right = left + SENSOR_BBOX_WIDTH;
	bottom = top + SENSOR_BBOX_HEIGHT;
}

void Sensor::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (enemy == NULL || enemy->IsDeleted()) {
		this->Delete();
		return;
	}
	RedKoopa* koopa = dynamic_cast<RedKoopa*>(enemy);
	if (koopa->GetState() == Koopa::KNOCK_OUT)
	{
		this->Delete();
		return;
	}
	if (koopa->IsOnGround() && koopa->GetState() == RedKoopa::HAS_NO_WING)
		this->TurnOn();
	else
		this->TurnOff();
	if (isOn == false)
		return;
	// Update the sensor position based on the enemy's position
	vy += ay * dt;
	FollowEnemy();
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void Sensor::FollowEnemy()
{
	RedKoopa* koopa = dynamic_cast<RedKoopa*>(enemy);
	int direction = koopa->GetDirection();
	float tempt;
	//koopa->GetPosition(this->x, tempt);
	koopa->GetPosition(this->x, this->y);
	if (direction == 1)
	{
		//this->x += ENEMY_BBOX_WIDTH / 2 + SENSOR_BBOX_WIDTH / 2 + 1;
		this->x +=  1;
	}
	else
	{
		//this->x -= ENEMY_BBOX_WIDTH / 2 + SENSOR_BBOX_WIDTH / 2 + 1;
		this->x -= 1;
	}
}
void Sensor::OnNoCollision(DWORD dt)
{
	//DebugOut(L"khong cham\n");
	if (isOn == false)
		return;
	RedKoopa* koopa = dynamic_cast<RedKoopa*>(enemy);
	koopa->ChangeDirection();
	float tempt;
	koopa->GetPosition(tempt, this->y);
}

void Sensor::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (isOn == false)
		return;
	if (!e->obj->IsBlocking())
	{
		return;
	}

	//if (dynamic_cast<CGoomba*>(e->obj)) return;
	// va cham voi nhung vat co kha nang block
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}
