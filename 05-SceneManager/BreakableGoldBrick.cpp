#include "BreakableGoldBrick.h"
#include "Mario.h"
void BreakableGoldBrick::GoUp(DWORD dt)
{
	if (this->y - dt * SPEED_Y > this->minY)
		this->y -= dt * SPEED_Y;
	else
	{
		this->y = this->minY;
		SetState(STATE_GO_DOWN);
	}
}

void BreakableGoldBrick::GoDown(DWORD dt)
{
	if (this->y + dt * SPEED_Y < this->maxY)
		this->y += dt * SPEED_Y;
	else
	{
		this->y = this->maxY;
		SetState(STATE_IDLE);
	}
}

void BreakableGoldBrick::GotHit(LPCOLLISIONEVENT e)
{
	// neu src_obj la mario nho thi khong bi anh huong 
	bool isMarioSmall = (dynamic_cast<CMario*>(e->src_obj)->GetLevel() == MARIO_LEVEL_SMALL);
	if (isMarioSmall)
	{
		SetState(STATE_GO_UP);
		return;
	}
	// them effect vo
	// delete this;
	this->Delete();
}

void BreakableGoldBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
