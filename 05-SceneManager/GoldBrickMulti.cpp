#include "GoldBrickMulti.h"
#include "Mario.h"
void GoldBrickMulti::GoUp(DWORD dt)
{
	if (this->y - dt * SPEED_Y > this->minY)
		this->y -= dt * SPEED_Y;
	else
	{
		this->y = this->minY;
		SetState(STATE_GO_DOWN);
	}
}

void GoldBrickMulti::GoDown(DWORD dt)
{
	if (this->y + dt * SPEED_Y < this->maxY)
		this->y += dt * SPEED_Y;
	else
	{
		this->y = this->maxY;
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
		SetState(STATE_GO_UP);
		timer = GetTickCount64();
	}
	else
	{
		if (GetTickCount64() - timer >= TIME_TO_OFF)
		{
			SetState(STATE_GO_UP);
			this->active = false;
			timer = -1;
		}
		else
		{
			SetState(STATE_GO_UP);
			// them effect
		}
	}
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
}
