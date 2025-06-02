#include "GoldBrickWithButton.h"
#include "Button.h"
#include "PlayScene.h"
#include "Koopa.h"
#define STATE_IDLE 0
#define STATE_GO_UP 1
#define STATE_GO_DOWN 2
void GoldBrickWithButton::GotHit(LPCOLLISIONEVENT e)
{
	if (!this->active)
		return;
	SetState(STATE_GO_UP); // set state di len tren
	//button->IsAppear();
	this->active = false;
}
void GoldBrickWithButton::GoUp(DWORD dt)
{
	vy = -SPEED_Y; // di chuyen len tren
	if (this->y - dt * SPEED_Y <= this->minY)
	{
		this->y = this->minY;
		SetState(STATE_GO_DOWN);
	}
}

void GoldBrickWithButton::GoDown(DWORD dt)
{
	vy = SPEED_Y; // di chuyen xuong duoi
	if (this->y + dt * SPEED_Y >= this->maxY)
	{
		this->y = this->maxY;
		vy = 0; // dung lai
		SetState(STATE_IDLE);
		button->IsAppear();
	}
}

void GoldBrickWithButton::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == STATE_GO_UP)
	{
		Koopa* koopa = dynamic_cast<Koopa*>(e->obj);
		if (koopa != nullptr)
			koopa->KickedFromBottom(this); // koopa bi brick hit len tren
	}
}

void GoldBrickWithButton::OnNoCollision(DWORD dt)
{
	this->y += vy * dt;
}

void GoldBrickWithButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
