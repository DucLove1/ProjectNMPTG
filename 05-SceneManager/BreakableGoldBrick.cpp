#include "BreakableGoldBrick.h"
#include "Mario.h"
#include "Sprites.h"
#define ID_SPRITE_COIN 40001
#define TIME_COIN_TO_BRICK 10000
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
	if (this->state == STATE_COIN)
	{
		// cong tien cho mario
		// delete this;
		this->Delete();
		return;
	}
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
	case STATE_COIN:
		UpdateStateCoin();
		break;
	}
}
void BreakableGoldBrick::UpdateStateCoin()
{
	if(GetTickCount64() - timerCoinState > TIME_COIN_TO_BRICK)
	{
		//timerCoinState = -1;
		SetState(STATE_IDLE);
	}

}
void BreakableGoldBrick::ChangeToCoin()
{
	SetState(STATE_COIN);
	timerCoinState = GetTickCount64();
}

void BreakableGoldBrick::Render()
{
	if (this->state == STATE_COIN)
	{
		// render hinh xu
		CSprites::GetInstance()->Get(ID_SPRITE_COIN)->Draw(x, y);
		return;
	}
	// render hinh gold brick
	GoldBrick::Render();
}
