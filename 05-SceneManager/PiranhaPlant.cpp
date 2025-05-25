#include "PiranhaPlant.h"
#include "GameClock.h"
#include "PlayScene.h"
#include "Effect.h"
#define DIFF 5.0f
void PiranhaPlant::UpdateStateAppear(DWORD dt)
{
	if (this->y - SPEED_Y * dt > minY)
	{
		this->y -= SPEED_Y * dt;
	}
	else
	{
		this->y = minY;
		if (timer == -1)
			timer = GameClock::GetInstance()->GetTime();
		else if (GameClock::GetInstance()->GetTime() - timer > TIME_WAIT_TO_HIDE)
		{
			SetState(HIDE);
			timer = -1;
		}
	}
}

void PiranhaPlant::UpdateStateHide(DWORD dt)
{
	if (this->y + SPEED_Y * dt < maxY)
	{
		this->y += SPEED_Y * dt;
	}
	else
	{
		this->y = maxY;
		if (timer == -1)
			timer = GameClock::GetInstance()->GetTime();
		else
		{
			float mX, mY;
			mario->GetPosition(mX, mY);
			if(abs(mX - this->x) < DISTANCE_TO_APPEAR)
			{
				return;
			}
			if (GameClock::GetInstance()->GetTime() - timer > TIME_WAIT_TO_APPEAR)
			{
				SetState(APPEAR);
				timer = -1;
			}
		}
	}
}

void PiranhaPlant::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_PIRANHA_PLANT)->Render(x, y);
}

void PiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	switch (state)
	{
	case APPEAR:
		UpdateStateAppear(dt);
		break;
	case HIDE:
		UpdateStateHide(dt);
		break;
	}
}

void PiranhaPlant::SetState(int state)
{
	CGameObject::SetState(state);
}

void PiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if(y == maxY)
	{
		left = top = right = bottom = 0;
		return;
	}
	left = x - PIRANHA_PLANT_BBOX_WIDTH / 2;
	top = y - PIRANHA_PLANT_BBOX_HEIGHT / 2;
	right = left + PIRANHA_PLANT_BBOX_WIDTH;
	bottom = top + PIRANHA_PLANT_BBOX_HEIGHT;
}

void PiranhaPlant::KnockedOut(CGameObject*)
{
	Delete();
	Effect* effect = new Effect(x, y - 8, EFFECT_DISAPPEAR);
	LPPLAYSCENE scene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	scene->AddObject(effect);
}

void PiranhaPlant::KickedFromBottom(CGameObject* object)
{
	KnockedOut(object);
}
