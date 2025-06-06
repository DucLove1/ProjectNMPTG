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

#define OUT_LINE 25.0f

#define MAX_VY_FALLING 0.05f

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

	if (player == nullptr) GotLinked();
	if (player == nullptr || player->IsDeleted()) return;

	float m_vx, m_vy;
	player->GetSpeed(m_vx, m_vy);

	if (isTouched) {
		//vy = MAX_VY_FALLING;
		vy += GRAVITY;
		if (hasPlayer)
		{
			player->SetIsStickToPlatform(this);  // Stick Mario to this platform
		}
	}

	x += vx * dt;
	y += vy * dt;

	CCollision::GetInstance()->Process(this, dt, coObjects);

	//if (player != nullptr && !player->IsLinkedUp() && !player->IsLinkedLeft())
	//	this->player = nullptr;

	//if (player != nullptr)
	//{
	//	if (player->IsLinkedLeft()) {
	//		float mx, my;
	//		float marioBBox = (player->GetLevel() == MARIO_LEVEL_SMALL) ? MARIO_SMALL_BBOX_WIDTH : MARIO_BIG_BBOX_WIDTH;
	//		player->GetPosition(mx, my);
	//		player->SetPosition(this->x - (DROP_LIFT_BBOX_WIDTH / 2 + marioBBox / 2) - 1, my);
	//	}
	//	else if (player->IsLinkedUp())
	//	{
	//		float mx, my;
	//		float marioBBox = (player->GetLevel() == MARIO_LEVEL_SMALL) ? MARIO_SMALL_BBOX_HEIGHT : MARIO_BIG_BBOX_HEIGHT;
	//		player->GetPosition(mx, my);
	//		player->SetPosition(mx, this->y - (DROP_LIFT_BBOX_HEIGHT / 2 + marioBBox / 2));
	//		float mvx, mvy;
	//		player->GetSpeed(mvx, mvy);
	//		player->SetSpeed(mvx, this->vy + 0.0025f);
	//	}
	//}

	float mx, my;
	player->GetPosition(mx, my); // player was checked

	float pl_left, pl_top, pl_right, pl_bottom;
	GetBoundingBox(pl_left, pl_top, pl_right, pl_bottom);



	bool outOfBounds =
		mx < pl_left - OUT_LINE ||
		mx > pl_right + OUT_LINE ||
		my < pl_top - OUT_LINE ||
		my > pl_bottom + OUT_LINE;

	if (outOfBounds && hasPlayer) {
		if (player->IsLinked())
		{
			player->SetIsStickToPlatform(NULL);
		}
		hasPlayer = false;
	}

}

void DropLift::OnNoCollision(DWORD dt)
{
	/*x += vx * dt;
	y += vy * dt;*/
}
void DropLift::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*> (e->obj))
	{
		OnCollidedWithMario(e);
	}
}
void DropLift::OnCollidedWithMario(LPCOLLISIONEVENT e) {
	if (player == NULL) GotLinked();
	if (player->GetState() == MARIO_STATE_DIE) return;

	if (e->ny < 0 && !isTouched) {
		isTouched = true;
		hasPlayer = true;
		vx = 0;
		vy = MAX_VY_FALLING;
	}
	else if (e->nx != 0 && vx != 0) {
		player->SetIsStickToPlatform(this);
		hasPlayer = true;
	}
}

bool DropLift::IsOnCamera()
{
	float posLeft;
	float posRight;
	float posTop;
	float posBottom;
	posLeft = x - DROP_LIFT_BBOX_WIDTH / 2;
	posRight = x + DROP_LIFT_BBOX_WIDTH /2;
	posTop = y - DROP_LIFT_BBOX_HEIGHT / 2;
	posBottom = y + DROP_LIFT_BBOX_HEIGHT / 2;
	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);
	if ((posLeft >= camX && posLeft <= camX + SCREEN_WIDTH) ||
		(posRight >= camX && posRight <= camX + SCREEN_WIDTH))
		return true;

	return false;
	//if (this->x - DROP_LIFT_BBOX_WIDTH <= camX + SCREEN_WIDTH && this->x >= camX
	//	&& this->y <= camY + SCREEN_HEIGHT && this->y >= camY)
	//	return true;
	//return false;
}

void DropLift::GotLinked()
{
	CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (scene != nullptr) {
		CMario* player = dynamic_cast<CMario*>(scene->GetPlayer());
		if (player != nullptr)
			this->player = player;
	}
}