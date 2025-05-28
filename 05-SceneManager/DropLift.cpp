#include "DropLift.h"
#include "Sprites.h"
#include "Mario.h"
#include "GoldBrick.h"
#include "Game.h"
#define DROP_LIFT_BBOX_WIDTH 48
#define DROP_LIFT_BBOX_HEIGHT 16
#define ID_SPRITE_DROP_LIFT 560000
#define SCREEN_HEIGHT 268
#define SCREEN_WIDTH 274

#define MAX_VY_FALLING 0.5f

int DropLift::IsCollidable()
{
	return 1;
}

void DropLift::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - DROP_LIFT_BBOX_WIDTH / 2;
	top = y - DROP_LIFT_BBOX_HEIGHT / 2;
	right = left + DROP_LIFT_BBOX_WIDTH;
	bottom = top + DROP_LIFT_BBOX_HEIGHT;
}

void DropLift::Render()
{
	CSprites::GetInstance()->Get(ID_SPRITE_DROP_LIFT)->Draw(x, y);
}

void DropLift::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isActive && IsOnCamera())
		isActive = true;
	if (!isActive)
		return;
	if (!isTouched)
	{
		vx = -0.02f; // Move left
		vy = 0; // No vertical movement
	}
	else
	{
		vx = 0;
		vy = 0.05f;//
	}

	x += vx * dt;
	y += vy * dt;
	//if(player!=nullpter)


	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (player != nullptr && !player->IsLinkedUp() && !player->IsLinkedLeft())
		this->player = nullptr;

	if (player != nullptr)
	{
		if (player->IsLinkedLeft()) {
			float mx, my;
			float marioBBox = (player->GetLevel() == MARIO_LEVEL_SMALL) ? MARIO_SMALL_BBOX_WIDTH : MARIO_BIG_BBOX_WIDTH;
			player->GetPosition(mx, my);
			player->SetPosition(this->x - (DROP_LIFT_BBOX_WIDTH / 2 + marioBBox / 2) - 1, my);
		}
		else if (player->IsLinkedUp())
		{
			float mx, my;
			float marioBBox = (player->GetLevel() == MARIO_LEVEL_SMALL) ? MARIO_SMALL_BBOX_HEIGHT : MARIO_BIG_BBOX_HEIGHT;
			player->GetPosition(mx, my);
			player->SetPosition(mx, this->y - (DROP_LIFT_BBOX_HEIGHT / 2 + marioBBox / 2));
			float mvx, mvy;
			player->GetSpeed(mvx, mvy);
			player->SetSpeed(mvx, this->vy + 0.0025f);
		}
	}
}

void DropLift::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void DropLift::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (dynamic_cast<CMario*>(e->obj))
	//{
	//	CMario* mario = dynamic_cast<CMario*>(e->obj);
	//	if (e->nx < 0)
	//	{
	//		float marioBBox = (mario->GetLevel() == MARIO_LEVEL_SMALL) ? MARIO_SMALL_BBOX_WIDTH : MARIO_BIG_BBOX_WIDTH;
	//		float mx, my;
	//		mario->GetPosition(mx, my);
	//		mario->SetPosition(this->x - (DROP_LIFT_BBOX_WIDTH / 2 + marioBBox / 2)-1, my);
	//	}
	//}
}

bool DropLift::IsOnCamera()
{
	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);
	if (this->x - DROP_LIFT_BBOX_WIDTH <= camX + SCREEN_WIDTH && this->x >= camX
		&& this->y <= camY + SCREEN_HEIGHT && this->y >= camY)
		return true;
	return false;
}

void DropLift::GotLinked()
{

	this->player = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (player == nullptr)
		DebugOut(L"[ERROR] CPipe::SetPlayer - player is nullptr\n");
}