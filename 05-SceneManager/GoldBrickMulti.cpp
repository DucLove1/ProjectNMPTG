#include "GoldBrickMulti.h"
#include "Mario.h"
#include "Koopa.h"
#include "GameClock.h"
void GoldBrickMulti::GoUp(DWORD dt)
{
	vy = -SPEED_Y; // di chuyen len tren
	if (this->y - dt * SPEED_Y <= this->minY)
	{
		this->y = this->minY;
		SetState(STATE_GO_DOWN);
	}
}

void GoldBrickMulti::GoDown(DWORD dt)
{
	vy = SPEED_Y; // di chuyen xuong duoi
	if (this->y + dt * SPEED_Y >= this->maxY)
	{
		this->y = this->maxY;
		vy = 0; // dung lai
		SetState(STATE_IDLE);
	}
}

void GoldBrickMulti::GotHit(LPCOLLISIONEVENT e)
{
	if (this->active == false)
		return;
	// them effect
	if (timer == -1)
	{
		// them effect
		//SetState(STATE_GO_UP);
		timer = GameClock::GetInstance()->GetTime();
	}
	else
	{
		if (GameClock::GetInstance()->GetTime() - timer >= TIME_TO_OFF)
		{
			//SetState(STATE_GO_UP);
			this->active = false;
			timer = -1;
		}
		else
		{
			//SetState(STATE_GO_UP);
			// them effect
		}
	}
	this->isBouncing = true;
}

void GoldBrickMulti::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->active == false && this->state == STATE_IDLE)
		return;
	switch (state)
	{
	case STATE_IDLE:
		break;
	case STATE_GO_UP:
		GoUp(dt);
		break;
	case STATE_GO_DOWN:
		GoDown(dt);
		break;
	}
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}

void GoldBrickMulti::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == STATE_GO_UP)
	{
		Koopa* koopa = dynamic_cast<Koopa*>(e->obj);
		if (koopa != nullptr)
			koopa->KickedFromBottom(this); // koopa bi brick hit len tren
	}
}
void GoldBrickMulti::OnNoCollision(DWORD dt)
{
	this->y += vy * dt;
}