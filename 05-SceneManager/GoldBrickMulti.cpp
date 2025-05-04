#include "GoldBrickMulti.h"
#include "Mario.h"
void GoldBrickMulti::GoUp(DWORD dt)
{
	if(this->y - dt * SPEED_Y > this->minY)
		this->y -= dt * SPEED_Y;
	else
	{
		this->y = this->minY;
		SetState(STATE_GO_DOWN);
	}
}

void GoldBrickMulti::GoDown(DWORD dt)
{
	if(this->y + dt * SPEED_Y < this->maxY)
		this->y += dt * SPEED_Y;
	else
	{
		this->y = this->maxY;
		SetState(STATE_IDLE);
	}
}

void GoldBrickMulti::GotHit(LPCOLLISIONEVENT e)
{
	// them effect
	// tru so lan hit
	if (this->times > 0)
	{
		SetState(STATE_GO_UP);
		// neu la mario nho thi khong tru so lan hit
		/*bool isMarioSmall = (dynamic_cast<CMario*>(e->src_obj)->GetLevel() == MARIO_LEVEL_SMALL);
		if(!isMarioSmall)
			this->times--;*/
		this->times--;
	}
	// tat active	
	if (this->times == 0)
		this->active = false;
}

void GoldBrickMulti::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->active == false)
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
