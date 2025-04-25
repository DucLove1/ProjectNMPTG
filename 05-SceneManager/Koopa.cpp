#include "Koopa.h"
#include "Goomba.h"
#include "AssetIDs.h"
#include "Mario.h"
void Koopa::SetState(int state)
{
	switch (state)
	{
	case HAS_WING:
		SetStateHasWing();
		break;
	case HAS_NO_WING:
		SetStateHasNoWing();
		break;
	case IN_SHELL_UP:
		SetStateInShellUp();
		break;
	case IN_SHELL_DOWN:
		SetStateInShellDown();
		break;
	case KNOCK_OUT:
		SetStateKnockOut();
		break;
	
	}
	CGameObject::SetState(state);
}

void Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	switch (state)
	{
	case HAS_WING:
		left = x - KOOPA_SPRITE_HAS_WING_WIDTH / 2;
		top = y - KOOPA_SPRITE_HAS_WING_HEIGHT / 2;
		right = left + KOOPA_SPRITE_HAS_WING_WIDTH;
		bottom = top + KOOPA_SPRITE_HAS_WING_HEIGHT;
		break;
	case HAS_NO_WING:
	case KNOCK_OUT:
		left = x - KOOPA_SPRITE_HAS_NO_WING_WIDTH / 2;
		top = y - KOOPA_SPRITE_HAS_NO_WING_HEIGHT / 2;
		right = left + KOOPA_SPRITE_HAS_NO_WING_WIDTH;
		bottom = top + KOOPA_SPRITE_HAS_NO_WING_HEIGHT;
		break;
	case IN_SHELL_UP:
	case IN_SHELL_DOWN:
		left = x - KOOPA_SPRITE_IN_SHELL_WIDTH / 2;
		top = y - KOOPA_SPRITE_IN_SHELL_HEIGHT / 2;
		right = left + KOOPA_SPRITE_IN_SHELL_WIDTH;
		bottom = top + KOOPA_SPRITE_IN_SHELL_HEIGHT;
		break;

	}
}

void Koopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	onGround = false;
}

void Koopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	// va cham vs goomba thi knock out no
	//if (dynamic_cast<CGoomba*>(e->obj) &&
	//	(this->state == IN_SHELL_DOWN || this->state == IN_SHELL_UP) &&
	//	vx != 0)
	//{
	//	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	//	if (goomba->IsAlive())
	//	{
	//		goomba->KnockedOut(this);
	//	}
	//}
	OnCollisionWithEnemy(e);
	// khong bi block boi e->obj thi return
	if (!e->obj->IsBlocking())
		return;
	// bi block boi e->obj thi xu ly
	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0)
			onGround = true;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		nx = -nx;
	}
}
void Koopa::OnCollisionWithEnemy(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CEnemy*>(e->obj) &&
		(this->state == IN_SHELL_DOWN || this->state == IN_SHELL_UP) &&
		vx != 0)
	{
		CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
		if (enemy->IsAlive())
		{
			Koopa* koopa = dynamic_cast<Koopa*>(e->obj);
			if (koopa != NULL)
			{
				if (koopa->GetState() == Koopa::IN_SHELL_DOWN || koopa->GetState() == Koopa::IN_SHELL_UP)
				{
					float vx, vy;
					koopa->GetSpeed(vx, vy);
					if(vx != 0)
						this->KnockedOut(koopa);
				}
			}
			enemy->KnockedOut(this);
		}
	}
}
void Koopa::UpdateStateInShell()
{
	ULONGLONG cur = GetTickCount64();
	if (vx == 0 && cur - timerInShell >= TIME_OUT_OF_SHELL)
	{
		SetState(HAS_NO_WING);
		timerInShell = 0;
	}
}
void Koopa::UpdateStateKnockOut()
{
	ULONGLONG time = GetTickCount64() - timerKnockOut;
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
void Koopa::Render()
{
	int aniId = ID_ANI_GREEN_KOOPA_WALKING_LEFT;
	switch (state)
	{
	case HAS_WING:
		if (vx < 0)
			aniId = (type == RED_KOOPA) ? ID_ANI_RED_KOOPA_WING_LEFT : ID_ANI_GREEN_KOOPA_WING_LEFT;
		else
			aniId = (type == RED_KOOPA) ? ID_ANI_RED_KOOPA_WING_RIGHT : ID_ANI_GREEN_KOOPA_WING_RIGHT;
		break;
	case HAS_NO_WING:
		if (vx < 0)
			aniId = (type == RED_KOOPA) ? ID_ANI_RED_KOOPA_WALKING_LEFT : ID_ANI_GREEN_KOOPA_WALKING_LEFT;
		else
			aniId = (type == RED_KOOPA) ? ID_ANI_RED_KOOPA_WALKING_RIGHT : ID_ANI_GREEN_KOOPA_WALKING_RIGHT;
		break;
	case IN_SHELL_UP:
		if (vx == 0)
			aniId = (type == RED_KOOPA) ? ID_ANI_RED_KOOPA_IN_SHELL_UP : ID_ANI_GREEN_KOOPA_IN_SHELL_UP;
		else
			aniId = (type == RED_KOOPA) ? ID_ANI_RED_KOOPA_IN_SHELL_UP_MOVE : ID_ANI_GREEN_KOOPA_IN_SHELL_UP_MOVE;
		break;
	case IN_SHELL_DOWN:
		if (vx == 0)
			aniId = (type == RED_KOOPA) ? ID_ANI_RED_KOOPA_IN_SHELL_DOWN : ID_ANI_GREEN_KOOPA_IN_SHELL_DOWN;
		else
			aniId = (type == RED_KOOPA) ? ID_ANI_RED_KOOPA_IN_SHELL_DOWN_MOVE : ID_ANI_GREEN_KOOPA_IN_SHELL_DOWN_MOVE;
		break;
	case KNOCK_OUT:
		    aniId = (type == RED_KOOPA) ? ID_ANI_RED_KOOPA_KNOCK_OUT : ID_ANI_GREEN_KOOPA_KNOCK_OUT;
		break;
	}
	if (lastAnimationId != aniId)
	{
		CAnimations::GetInstance()->Get(aniId)->Reset();
		lastAnimationId = aniId;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
void Koopa::KickedFromTop(CGameObject* obj)
{
	if (state == HAS_WING)
	{
		SetState(HAS_NO_WING);
	}
	else if (state == HAS_NO_WING)
	{
		SetState(IN_SHELL_DOWN);
	}
	else if (state == IN_SHELL_UP || state == IN_SHELL_DOWN)
	{
		if (vx != 0)
		{
			vx = 0;
			timerInShell = GetTickCount64();
			return;
		}
		float objX, objY;
		obj->GetPosition(objX, objY);
		if (objX < this->x)
		{
			MoveInShell(1);
		}
		else
			MoveInShell(-1);
	}
}
void Koopa::MoveInShell(int direction)
{
	this->nx = direction;
	vx = direction * KOOPA_IN_SHELL_SPEED;
}
void Koopa::KnockedOut(CGameObject* obj)
{
	float objX, objY;
	obj->GetPosition(objX, objY);
	nx = (this->x > objX) ? 1 : -1;
	SetState(KNOCK_OUT);
}
void Koopa::SetStateHasWing()
{

}
void Koopa::SetStateHasNoWing()
{
	if (this->state == HAS_WING)
	{
		y += (KOOPA_SPRITE_HAS_WING_HEIGHT - KOOPA_SPRITE_HAS_NO_WING_HEIGHT) / 2;
	}
	else if (this->state == IN_SHELL_DOWN || this->state == IN_SHELL_UP)
	{
		vx = KOOPA_WALKING_SPEED * nx;
		y -= (KOOPA_SPRITE_HAS_NO_WING_HEIGHT - KOOPA_SPRITE_IN_SHELL_HEIGHT) / 2;
	}
}
void Koopa::SetStateInShellUp()
{
	vx = 0;
	timerInShell = GetTickCount64();
	if (this->state == HAS_NO_WING)
	{
		y += (KOOPA_SPRITE_HAS_NO_WING_HEIGHT - KOOPA_SPRITE_IN_SHELL_HEIGHT) / 2;
	}
	else if (this->state == HAS_WING)
	{
		y += (KOOPA_SPRITE_HAS_WING_HEIGHT - KOOPA_SPRITE_IN_SHELL_HEIGHT) / 2;
	}
}

void Koopa::SetStateInShellDown()
{
	vx = 0;
	timerInShell = GetTickCount64();
	if (this->state == HAS_NO_WING)
	{
		y += (KOOPA_SPRITE_HAS_NO_WING_HEIGHT - KOOPA_SPRITE_IN_SHELL_HEIGHT) / 2;
	}
	else if (this->state == HAS_WING)
	{
		y += (KOOPA_SPRITE_HAS_WING_HEIGHT - KOOPA_SPRITE_IN_SHELL_HEIGHT) / 2;
	}
}

void Koopa::SetStateKnockOut()
{
	if (state == HAS_WING)
	{
		y += (KOOPA_SPRITE_HAS_WING_HEIGHT - KOOPA_SPRITE_HAS_NO_WING_HEIGHT) / 2;
	}
	ay = -GOOMBA_GRAVITY;
	vy = -0.01f;
	ax = -nx * 0.0005f;
	//vx = abs(vx) * nx;
	vx = 0.25f * nx;
	timerKnockOut = GetTickCount64();
}


void Koopa::ReleaseByPlayer(CMario* player)
{
	//CMario* player = dynamic_cast<CMario*>(e->obj);
	if (player == NULL) return;
	int nx = player->GetNx();
	if (this->state == IN_SHELL_DOWN) {
		if(nx >= 0)
			MoveInShell(1);
		else
			MoveInShell(-1);
	}
}
