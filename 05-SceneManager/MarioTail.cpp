#include "MarioTail.h"
#include <algorithm>

#include "Mario.h"
#include "CEnemy.h"
#include "Koopa.h"
#include "Goomba.h"
#include "CQuestionBrick.h"
#include "Breakable.h"
#include "Venus.h"
#include "Collision.h"
#include "BreakableGoldBrick.h"
#include "GoldBrickMulti.h"
#include "ItemGoldBrick.h"
#include "Button.h"
#include "GoldBrickWithButton.h"
#include "GameManager.h"
#include "PlayScene.h"
#include "Effect.h"
#define MARIO_BBOX_WIDTH 14

void CMarioTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isActive) return;
	this->player = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CMario* player = dynamic_cast<CMario*>(this->player);
	fdt = (float)dt;
	if (player == nullptr or player->IsDeleted())
		return;

	UpdateMNx(); //just update when not attack

	//if (startAttack != 0 && (GetTickCount64() - startAttack <= ATTACK_ROUND_TIME))
	//{
	//	//isWhiping = true; // set to true when attack
	//}
	//else
	//{
	//	//isWhiping = false;
	//}

	if (!isWhiping)
	{
		FollowPlayer(dt);
	}
	else
	{
		TailAttack(dt);
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CMarioTail::Render()
{
	if (!isActive) return;
	RenderBoundingBox();
}
void CMarioTail::OnNoCollision(DWORD dt)
{
	if (!isActive) return;
	x += (vx + atkVelocityX) * dt;
	y += (vy + atkVelocityY) * dt;
}
void CMarioTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!isActive) return;
	if (!isWhiping) return;

	if (dynamic_cast<CEnemy*>(e->obj)) // if e->obj is Leaf
	{
		float x, y;
		e->obj->GetPosition(x, y); // get position of enemy
		Effect* effect = new Effect(x, y, EFFECT_TAIL_ATTACK);
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(effect); // add effect to scene)
		dynamic_cast<CEnemy*>(e->obj)->KickedFromBottom(this);
		bool isKoopa = dynamic_cast<Koopa*>(e->obj) != nullptr; // check if it is a Koopa
		if (!isKoopa)
		{
			// cong 100đ va effect 100 khi knock out goomba
			Effect* scoreEffect = new Effect(x, y, 100);
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(scoreEffect);
			GameManager::GetInstance()->AddScore(100); // add score to game manager
		}
	}
	else if (dynamic_cast<CQuestionBrick*>(e->obj)) // if e->obj is QuestionBrick
	{
		dynamic_cast<CQuestionBrick*>(e->obj)->GotHit(e);
	}
	else if (dynamic_cast<GoldBrick*>(e->obj))
	{
		dynamic_cast<GoldBrick*>(e->obj)->GotHit(e);
	}


}

void CMarioTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TAIL_BBOX_WIDTH / 2;
	top = y - TAIL_BBOX_HEIGHT / 2;
	right = left + TAIL_BBOX_WIDTH;
	bottom = top + TAIL_BBOX_HEIGHT;
}
void CMarioTail::TailAttack(DWORD dt)
{
	if (!isActive) return;

	CMario* player = dynamic_cast<CMario*>(this->player);
	if (player == nullptr or player->IsDeleted())
		return;
	float Mx, My, fdt = (float)dt;
	player->GetPosition(Mx, My);
	float Mvx, Mvy;
	player->GetSpeed(Mvx, Mvy);

	float dx = (Mx + Mvx * fdt);
	float dy = (My + Mvy * fdt);
	Modify(dx, dy);
	//DebugOut(L"CAL\n");


	if (startAttack == 0) // start
	{
		startAttack = GetTickCount64();

		if (Mnx >= 0)
		{
			offSetLeft = dx - MARIO_BBOX_WIDTH;
			offSetRight = dx + MARIO_BBOX_WIDTH * 2;
		}
		else
		{
			offSetLeft = dx - MARIO_BBOX_WIDTH * 2;
			offSetRight = dx + MARIO_BBOX_WIDTH;
		}
		//DebugOut(L"SET VALUE \n");
	}


	if (GetTickCount64() - startAttack >= ATTACK_ROUND_TIME / 2 && GetTickCount64() - startAttack < ATTACK_ROUND_TIME) // state 2 return;
	{
		float _time = (ATTACK_ROUND_TIME / 2 );
		if (Mnx >= 0)
		{
			//SetSpeed((offSetLeft - x) / _time, (dy - y) / _time);
			SetSpeed((offSetLeft - x) / _time, 0);
		}
		else
		{
			//SetSpeed((offSetRight - x) / _time, (dy - y) / _time);
			SetSpeed((offSetRight - x) / _time, 0);
		}
		//DebugOut(L"STATE 2 \n");
	}
	else if (GetTickCount64() - startAttack >= ATTACK_ROUND_TIME) // was done, stop everything
	{
		isWhiping = false;
		startAttack = 0;
		//SetPosition(Mx, My);
		//DebugOut(L"NGƯNG RỒI ĐÓ NHA MÁ");
	}
	else// state 1 whiping 
	{
		float _time = (ATTACK_ROUND_TIME / 2);
		if (Mnx >= 0)
		{
			//SetSpeed((offSetRight - x) / _time, (dy - y) / _time);
			SetSpeed((offSetRight - x) / _time, 0);
		}
		else
		{
			//SetSpeed((offSetLeft - x) / _time, (dy - y) / _time);
			SetSpeed((offSetLeft - x) / _time, 0);
		}
		//DebugOut(L"STATE 1 \n");
	}
}


void CMarioTail::FollowPlayer(DWORD dt)
{
	CMario* player = dynamic_cast<CMario*>(this->player);
	if (player == nullptr or player->IsDeleted())
		return;

	float Mx, My, fdt = (float)dt;
	player->GetPosition(Mx, My);
	float Mvx, Mvy;
	player->GetSpeed(Mvx, Mvy);

	float dx = (Mx + Mvx * fdt) - x;
	float dy = (My + Mvy * fdt) - y;
	//modify targer pos of tail

	Modify(dx, dy);

	this->SetSpeed(dx / fdt, dy / fdt); // set speed to follow player
}
void CMarioTail::UpdateMNx()
{
	CMario* player = dynamic_cast<CMario*>(this->player);
	if (player == nullptr or player->IsDeleted())
		return;

	if (isWhiping == false)
	{
		Mnx = player->GetNx();
	}
}
void CMarioTail::Modify(float& modifyX, float& modifyY)
{
	modifyX += -Mnx * TAIL_BBOX_WIDTH / 2;
	modifyY += TAIL_BBOX_HEIGHT;
}
