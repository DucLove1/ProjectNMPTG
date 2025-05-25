#include "Goomba.h"
#include "GameClock.h"
#include "Wall.h"
void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state != DIE && state != KNOCK_OUT)
	{
		if (state == HAS_NO_WING)
		{
			left = x - GOOMBA_ALIVE_BBOX_WIDTH / 2;
			top = y - GOOMBA_ALIVE_BBOX_HEIGHT / 2;
			right = left + GOOMBA_ALIVE_BBOX_WIDTH;
			bottom = top + GOOMBA_ALIVE_BBOX_HEIGHT;
		}
		else if (state == HAS_WING)
		{
			float ajust = (GOOMBA_SPRITE_HEIGHT_WING - GOOMBA_ALIVE_BBOX_HEIGHT);
			left = x - GOOMBA_ALIVE_BBOX_WIDTH / 2;
			top = y - GOOMBA_SPRITE_HEIGHT_WING / 2 + ajust;
			right = left + GOOMBA_ALIVE_BBOX_WIDTH;
			bottom = top + GOOMBA_ALIVE_BBOX_HEIGHT - 1;
		}
	}
	else if (state == DIE)
	{
		left = x - GOOMBA_DIE_BBOX_WIDTH / 2;
		top = y - GOOMBA_DIE_BBOX_HEIGHT / 2;
		right = left + GOOMBA_DIE_BBOX_WIDTH;
		bottom = top + GOOMBA_DIE_BBOX_HEIGHT;
	}
	else
	{
		left = x - GOOMBA_ALIVE_BBOX_WIDTH / 2;
		top = y - GOOMBA_ALIVE_BBOX_HEIGHT / 2;
		right = left + GOOMBA_ALIVE_BBOX_WIDTH;
		bottom = top + GOOMBA_ALIVE_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	onGround = false;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj))
	{
		if (((CGoomba*)e->obj)->GetState() == this->GetState())
		{
			vx = -vx;
			float objVx, objVy;
			((CGoomba*)e->obj)->GetSpeed(objVx, objVy);
			((CGoomba*)e->obj)->SetSpeed(-objVx, objVy);
		}
		return;
	}
	if (!e->obj->IsBlocking())
	{
		return;
	}
	if (e->ny != 0 )
	{
		vy = 0;
		if (e->ny < 0)
			onGround = true;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;


	CGameObject::Update(dt, coObjects);
	UpdateState();
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGoomba::UpdateState()
{
	//DebugOut(L"on ground %d\n", onGround);
	if ((state == DIE) && (GameClock::GetInstance()->GetTime() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	if (state == HAS_WING)
	{
		ULONGLONG cur = GameClock::GetInstance()->GetTime();
		if (mario && cur - timerFollow <= TIME_FOLLOW)
		{
			float marioX, marioY;
			mario->GetPosition(marioX, marioY);
			if (abs(marioX - this->x) >= DISTANCE_FOLLOW)
			{
				if (marioX > this->x)
					vx = abs(vx);
				else
					vx = -abs(vx);
			}
		}
		if (countJump >= 3 && onGround && cur - timerFly >= TIME_FLYING)
		{
			vy = -GOOMBA_FLY_FORCE;
			countJump = 0;
			timerFly = GameClock::GetInstance()->GetTime();
		}
		else if (cur - timerFly >= TIME_JUMPING)
		{
			if (onGround)
			{
				vy = -GOOMBA_JUMPING_FORCE;
				countJump++;
			}
		}
	}
	else if (state == KNOCK_OUT)
	{
		ULONGLONG time = GameClock::GetInstance()->GetTime() - timerKnockOut;
		if (time >= TIME_OUT_KNOCK_OUT)
		{
			isDeleted = true;
			return;
		}
		if (time >= TIME_KNOCK_OUT)
		{
			ay = GOOMBA_GRAVITY * 1.5;
			ax = 0;
			return;
		}
	}
}


void CGoomba::Render()
{
	int aniId = (type == GOOMBA) ? ID_ANI_GOOMBA_WALKING : ID_ANI_RED_GOOMBA_WALKING;
	ULONGLONG cur = GameClock::GetInstance()->GetTime();
	switch (state)
	{
	case HAS_WING:
		if (cur - timerFly >= TIME_JUMPING and cur - timerFly < TIME_FLYING)
		{
			aniId = (type == GOOMBA) ? ID_ANI_GOOMBA_WALKING_WING_READY_FLY : ID_ANI_RED_GOOMBA_WALKING_WING_READY_FLY;
		}
		else if (!onGround)
		{
			aniId = (type == GOOMBA) ? ID_ANI_GOOMBA_WING_FLY : ID_ANI_RED_GOOMBA_WING_FLY;
		}
		else
			aniId = (type == GOOMBA) ? ID_ANI_GOOMBA_WALKING_WING : ID_ANI_RED_GOOMBA_WALKING_WING;
		break;
	case HAS_NO_WING:
		aniId = (type == GOOMBA) ? ID_ANI_GOOMBA_WALKING : ID_ANI_RED_GOOMBA_WALKING;
		break;
	case DIE:
		aniId = (type == GOOMBA) ? ID_ANI_GOOMBA_DIE : ID_ANI_RED_GOOMBA_DIE;
		break;
	case KNOCK_OUT:
		aniId = (type == GOOMBA) ? ID_ANI_GOOMBA_KNOCK_OUT : ID_ANI_RED_GOOMBA_KNOCK_OUT;
		break;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CGoomba::KickedFromTop(CGameObject*)
{
	switch (state)
	{
	case HAS_WING:
		SetState(HAS_NO_WING);
		break;
	case HAS_NO_WING:
		SetState(DIE);
		break;
	}
}

void CGoomba::KickedFromBottom(CGameObject*)
{
	KnockedOut(this);
}

void CGoomba::KnockedOut(CGameObject* obj)
{
	float objX, objY;
	obj->GetPosition(objX, objY);
	nx = (this->x > objX) ? 1 : -1;
	SetState(KNOCK_OUT);
}

void CGoomba::SetStateDie()
{
	die_start = GameClock::GetInstance()->GetTime();
	y += (GOOMBA_SPRITE_HEIGHT - GOOMBA_SPRITE_HEIGHT_DIE) / 2 + 1;
	vx = 0;
	vy = 0;
	ay = 0;
	ax = 0;
}

void CGoomba::SetStateHasNoWing()
{
	if (state == HAS_WING)
	{
		y -= (GOOMBA_SPRITE_HEIGHT_WING - GOOMBA_SPRITE_HEIGHT) / 2;
	}
}

void CGoomba::SetStateHasWing()
{
	timerFly = GameClock::GetInstance()->GetTime();
}

void CGoomba::SetStateKockOut()
{
	if (state == HAS_WING)
	{
		y += (GOOMBA_SPRITE_HEIGHT_WING - GOOMBA_SPRITE_HEIGHT) / 2;
	}
	ay = -0;
	vy = -0.15;
	ax = nx * 0.000001f;
	vx = abs(vx) * nx;
	timerKnockOut = GameClock::GetInstance()->GetTime();
}

void CGoomba::SetState(int state)
{
	switch (state)
	{
	case DIE:
		SetStateDie();
		break;
	case HAS_NO_WING:
		SetStateHasNoWing();
		break;
	case HAS_WING:
		SetStateHasWing();
	case KNOCK_OUT:
		SetStateKockOut();
		break;
	}
	CGameObject::SetState(state);
}
