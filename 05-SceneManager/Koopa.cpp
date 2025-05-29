#include "Koopa.h"
#include "Goomba.h"
#include "AssetIDs.h"
#include "Mario.h"
#include "GameClock.h"
#include "GoldBrick.h"
#include "Effect.h"
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
	if (IsHolded()) return;
	x += vx * dt;
	y += vy * dt;
	onGround = false;
	ay = KOOPA_GRAVITY;
}
void Koopa::OnCollisionWithGoldBrick(LPCOLLISIONEVENT e)
{
	GoldBrick* goldBrick = dynamic_cast<GoldBrick*>(e->obj);
	// check goldBrick
	if (!goldBrick)
		return;
	// khi koopa cham vao 2 ben cua brick
	if (e->nx != 0 &&
		(this->state == IN_SHELL_DOWN || this->state == IN_SHELL_UP) &&
		vx != 0 && !isHolded)
	{
		//GoldBrick* goldBrick = dynamic_cast<GoldBrick*>(e->obj);
		goldBrick->GotHit(e);
		return;
	}
	if (e->ny < 0 && goldBrick->IsBoucing())
		this->KickedFromBottom(goldBrick);
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


	if (dynamic_cast<CQuestionBrick*>(e->obj) &&
		(this->state == IN_SHELL_DOWN || this->state == IN_SHELL_UP) &&
		vx != 0 && !isHolded)
	{
		CQuestionBrick* QB = dynamic_cast<CQuestionBrick*>(e->obj);
		QB->GotHit(e);
	}
	//collision with gold brick
	if(dynamic_cast<GoldBrick*>(e->obj))
	OnCollisionWithGoldBrick(e);
	// khong bi block boi e->obj thi return
	if (!e->obj->IsBlocking())
		return;
	// bi block boi e->obj thi xu ly
	if (e->ny != 0)
	{
		GoldBrick* brick = dynamic_cast<GoldBrick*>(e->obj);
		if (brick)
		{
			if (brick->IsBoucing())
				return;
		}
		if (nx == 0)
			vx = 0;
		if (e->ny < 0)
		{
			onGround = true;
		}
		vy = 0;
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
					if (vx != 0)
					{
						this->KnockedOut(koopa);
					}
				}
			}
			float x, y;
			enemy->GetPosition(x, y);
			Effect* effect = new Effect(x, y, EFFECT_TAIL_ATTACK);
			(dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene()))->AddObject(effect);
			enemy->KnockedOut(this);
			if (isHolded) {
				/*isHolded = false;
				this->KnockedOut(this);*/
				this->Delete();
			}
		}
	}
}
void Koopa::UpdateStateInShell(DWORD dt)
{
	//ULONGLONG cur = GetTickCount64();
	ULONGLONG cur = GameClock::GetInstance()->GetTime();
	if (vx == 0 && cur - timerInShell >= TIME_OUT_OF_SHELL)
	{
		SetState(HAS_NO_WING);
		timerInShell = 0;
	}
	if (IsHolded())
	{
		x += vx * dt;
		y += vy * dt;
	}
}
void Koopa::UpdateStateKnockOut(DWORD dt)
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
	if (IsHolded())
	{
		x += vx * dt;
		y += vy * dt;
	}
}
void Koopa::Render()
{
	int aniId = ID_ANI_GREEN_KOOPA_WALKING_LEFT;
	switch (state)
	{
	case HAS_WING:
		if (vx <= 0)
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
		if (nx == 0)
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

	if (this->isHolded)
	{
		aniId = (type == RED_KOOPA) ? ID_ANI_RED_KOOPA_IN_SHELL_DOWN : ID_ANI_GREEN_KOOPA_IN_SHELL_DOWN;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
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
			this->preNx = (this->nx != 0) ? this->nx : this->preNx;
			this->nx = 0;
			timerInShell = GameClock::GetInstance()->GetTime();
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
void Koopa::KickedFromBottom(CGameObject* obj)
{
	float x, y;
	obj->GetPosition(x, y);
	int direction = (this->x > x) ? 1 : -1;
	this->vy = -0.3f;
	this->vx = direction * 0.03f;
	//this->ax = 0.000001f * nx;
	this->y -= 1.0f;
	this->preNx = (this->nx != 0) ? this->nx : this->preNx;
	SetState(IN_SHELL_UP);
	if (type == RED_KOOPA)
		CAnimations::GetInstance()->Get(ID_ANI_RED_KOOPA_IN_SHELL_UP)->Reset();
	else if (type == GREEN_KOOPA)
		CAnimations::GetInstance()->Get(ID_ANI_GREEN_KOOPA_IN_SHELL_UP)->Reset();
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
		this->nx = this->preNx;
		vx = KOOPA_WALKING_SPEED * nx;
		y -= (KOOPA_SPRITE_HAS_NO_WING_HEIGHT - KOOPA_SPRITE_IN_SHELL_HEIGHT) / 2;
	}
}
void Koopa::SetStateInShellUp()
{
	//vx = 0;
	this->nx = 0;
	timerInShell = GameClock::GetInstance()->GetTime();
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
	this->nx = 0;
	timerInShell = GameClock::GetInstance()->GetTime();
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
	timerKnockOut = GameClock::GetInstance()->GetTime();
}


void Koopa::ReleaseByPlayer(CMario* player)
{
	//CMario* player = dynamic_cast<CMario*>(e->obj);
	if (player == NULL) return;
	int nx = player->GetNx();
	if (this->state == IN_SHELL_DOWN) {
		if (nx >= 0)
			MoveInShell(1);
		else
			MoveInShell(-1);
	}
}
