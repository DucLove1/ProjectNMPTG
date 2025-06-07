#include "BreakableGoldBrick.h"
#include "Mario.h"
#include "Sprites.h"
#include "GameClock.h"
#include "EffectBreak.h"
#include "Koopa.h"
#include "MarioTail.h"
#define ID_SPRITE_COIN 40001
#define TIME_COIN_TO_BRICK 10000
void BreakableGoldBrick::GoUp(DWORD dt)
{
	vy = -SPEED_Y; // di chuyen len tren
	if( this->y - dt * SPEED_Y <= this->minY)
	{
		this->y = this->minY;
		SetState(STATE_GO_DOWN);
	}
}

void BreakableGoldBrick::GoDown(DWORD dt)
{
	vy = SPEED_Y; // di chuyen xuong duoi
	if(this->y + dt * SPEED_Y >= this->maxY)
	{
		this->y = this->maxY;
		vy = 0; // dung lai
		SetState(STATE_IDLE);
	}
}

void BreakableGoldBrick::GotHit(LPCOLLISIONEVENT e)
{
	CMario* mario = dynamic_cast<CMario*>(e->src_obj);
	if (this->state == STATE_COIN)
	{
		// cong tien cho mario
		// delete this;
		if (mario != nullptr)
		{
			GameManager::GetInstance()->PlusCoins(1);
			GameManager::GetInstance()->AddScore(50);
			this->Delete();
		}
		return;
	}
	// neu brick dang o trang thai brick va mario khong nhay tu duoi len thi return
	if (e->ny <= 0 && mario)
		return;
	// neu src_obj la mario nho thi khong bi anh huong 
	bool isMarioSmall = (mario != NULL) ? (mario->GetLevel() == MARIO_LEVEL_SMALL) : false;
	if (isMarioSmall)
	{
		//SetState(STATE_GO_UP);
		this->isBouncing = true;
		return;
	}
	// them effect vo
	EffectBreak* effect = new EffectBreak(this->x, this->y);
	// delete this;
	this->Delete();
}

void BreakableGoldBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->active == false)
		return;
	if (button != nullptr && button->GetState() == BUTTON_STATE_PRESSED)
	{
		ChangeToCoin();
		button = nullptr; // reset button after pressing
	}
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
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void BreakableGoldBrick::UpdateStateCoin()
{
	if (GameClock::GetInstance()->GetTime() - timerCoinState > TIME_COIN_TO_BRICK)
	{
		//timerCoinState = -1;
		SetState(STATE_IDLE);
	}

}
void BreakableGoldBrick::ChangeToCoin()
{
	SetState(STATE_COIN);
	timerCoinState = GameClock::GetInstance()->GetTime();
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
	//RenderBoundingBox();
}

//void BreakableGoldBrick::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//	if (state == STATE_GO_UP)
//	{
//		Koopa* koopa = dynamic_cast<Koopa*>(e->obj);
//		if (koopa != nullptr)
//			koopa->KickedFromBottom(this); // koopa bi brick hit len tren
//	}
//}
//void BreakableGoldBrick::OnNoCollision(DWORD dt)
//{
//	this->y += vy * dt;
//}
//void BreakableGoldBrick::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//	if (!(state == STATE_GO_UP))
//		return;
//	if (dynamic_cast<Koopa*>(e->obj))
//	{
//		dynamic_cast<Koopa*>(e->obj)->KickedFromBottom(this);
//	}
//}
