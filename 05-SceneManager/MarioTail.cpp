#include "MarioTail.h"
#include <algorithm>

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

void CMarioTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isActive) return;
	this->player = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CMario* player = dynamic_cast<CMario*>(this->player);
	if (player == nullptr or player->IsDeleted())
		return;
	UpdateMNx();
	FollowPlayer(dt);

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
	if (dynamic_cast<CEnemy*>(e->obj)) // if e->obj is Leaf
	{
		// handle collision with Leaf
	}
	else if (dynamic_cast<CQuestionBrick*>(e->obj)) // if e->obj is QuestionBrick
	{
		// handle collision with QuestionBrick
	}
}

void CMarioTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TAIL_BBOX_WIDTH / 2;
	top = y - TAIL_BBOX_HEIGHT / 2;
	right = left + TAIL_BBOX_WIDTH;
	bottom = top + TAIL_BBOX_HEIGHT;
}
void CMarioTail::CalTailAttack(int Mnx, DWORD dt)
{
	if (!isActive) return;
}
void CMarioTail::FollowPlayer(DWORD dt)
{
	CMario* player = dynamic_cast<CMario*>(this->player);
	if (player == nullptr or player->IsDeleted())
		return;

	if (!isWhiping) Mnx = player->GetNx();

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
