#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Koopa.h"
#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "CQuestionBrick.h"
#include "Breakable.h"
#include "Leaf.h"
#include "Koopa.h"
#include "Venus.h"
#include "VenusBullet.h"
#include "Collision.h"
#include "SpawnEnemy.h"
#include "BreakableGoldBrick.h"
#include "GoldBrickMulti.h"
#include "ItemGoldBrick.h"
#include "Button.h"
#include "GoldBrickWithButton.h"
#include "GameManager.h"
#include "DropLift.h"
//define for Id map
int mapAniId[][26] = {
		{
			ID_ANI_MARIO_SMALL_IDLE_RIGHT, ID_ANI_MARIO_SMALL_IDLE_LEFT,
			ID_ANI_MARIO_SMALL_WALKING_RIGHT, ID_ANI_MARIO_SMALL_WALKING_LEFT,
			ID_ANI_MARIO_SMALL_RUNNING_RIGHT, ID_ANI_MARIO_SMALL_RUNNING_LEFT,
			ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT, ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT,
			ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT, ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT,
			ID_ANI_MARIO_SMALL_BRACE_RIGHT, ID_ANI_MARIO_SMALL_BRACE_LEFT,
			ID_ANI_MARIO_SMALL_PICKING_IDLE_RIGHT, ID_ANI_MARIO_SMALL_PICKING_IDLE_LEFT,
			ID_ANI_MARIO_SMALL_PICKING_WALK_RIGHT, ID_ANI_MARIO_SMALL_PICKING_WALK_LEFT,
			ID_ANI_MARIO_SMALL_PICKING_RUN_RIGHT, ID_ANI_MARIO_SMALL_PICKING_RUN_LEFT,
			ID_ANI_MARIO_SMALL_PICKING_JUMP_RIGHT, ID_ANI_MARIO_SMALL_PICKING_JUMP_LEFT,
			ID_ANI_MARIO_SMALL_PICKING_RUN_JUMP_RIGHT, ID_ANI_MARIO_SMALL_PICKING_RUN_JUMP_LEFT,
			ID_ANI_MARIO_SMALL_IDLE_RIGHT, ID_ANI_MARIO_SMALL_IDLE_LEFT, // fill array with idle (this is sitting)
			ID_ANI_MARIO_SMALL_IDLE_RIGHT, ID_ANI_MARIO_SMALL_IDLE_LEFT // fill array with idle (this is powerUp)
		},
		{
			ID_ANI_MARIO_IDLE_RIGHT, ID_ANI_MARIO_IDLE_LEFT,
			ID_ANI_MARIO_WALKING_RIGHT, ID_ANI_MARIO_WALKING_LEFT,
			ID_ANI_MARIO_RUNNING_RIGHT, ID_ANI_MARIO_RUNNING_LEFT,
			ID_ANI_MARIO_JUMP_WALK_RIGHT, ID_ANI_MARIO_JUMP_WALK_LEFT,
			ID_ANI_MARIO_JUMP_RUN_RIGHT, ID_ANI_MARIO_JUMP_RUN_LEFT,
			ID_ANI_MARIO_BRACE_RIGHT, ID_ANI_MARIO_BRACE_LEFT,
			ID_ANI_MARIO_PICKING_IDLE_RIGHT, ID_ANI_MARIO_PICKING_IDLE_LEFT,
			ID_ANI_MARIO_PICKING_WALK_RIGHT, ID_ANI_MARIO_PICKING_WALK_LEFT,
			ID_ANI_MARIO_PICKING_RUN_RIGHT, ID_ANI_MARIO_PICKING_RUN_LEFT,
			ID_ANI_MARIO_PICKING_JUMP_RIGHT, ID_ANI_MARIO_PICKING_JUMP_LEFT,
			ID_ANI_MARIO_PICKING_RUN_JUMP_RIGHT, ID_ANI_MARIO_PICKING_RUN_JUMP_LEFT,
			ID_ANI_MARIO_SIT_RIGHT, ID_ANI_MARIO_SIT_LEFT,
			//ID_ANI_MARIO_POWERUP_TO_BIG_RIGHT, ID_ANI_MARIO_POWERUP_TO_BIG_LEFT
			ID_ANI_MARIO_SMALL_TO_BIG_RIGHT,ID_ANI_MARIO_SMALL_TO_BIG_LEFT
		},
		{
			ID_ANI_MARIO_TAIL_IDLE_RIGHT, ID_ANI_MARIO_TAIL_IDLE_LEFT,
			ID_ANI_MARIO_TAIL_WALKING_RIGHT, ID_ANI_MARIO_TAIL_WALKING_LEFT,
			ID_ANI_MARIO_TAIL_RUNNING_RIGHT, ID_ANI_MARIO_TAIL_RUNNING_LEFT,
			ID_ANI_MARIO_TAIL_JUMP_WALK_RIGHT, ID_ANI_MARIO_TAIL_JUMP_WALK_LEFT,
			ID_ANI_MARIO_TAIL_JUMP_RUN_RIGHT, ID_ANI_MARIO_TAIL_JUMP_RUN_LEFT,
			ID_ANI_MARIO_TAIL_BRACE_RIGHT, ID_ANI_MARIO_TAIL_BRACE_LEFT,
			ID_ANI_MARIO_TAIL_PICKING_IDLE_RIGHT, ID_ANI_MARIO_TAIL_PICKING_IDLE_LEFT,
			ID_ANI_MARIO_TAIL_PICKING_WALK_RIGHT, ID_ANI_MARIO_TAIL_PICKING_WALK_LEFT,
			ID_ANI_MARIO_TAIL_PICKING_RUN_RIGHT, ID_ANI_MARIO_TAIL_PICKING_RUN_LEFT,
			ID_ANI_MARIO_TAIL_PICKING_JUMP_RIGHT, ID_ANI_MARIO_TAIL_PICKING_JUMP_LEFT,
			ID_ANI_MARIO_TAIL_PICKING_RUN_JUMP_RIGHT, ID_ANI_MARIO_TAIL_PICKING_RUN_JUMP_LEFT,
			ID_ANI_MARIO_TAIL_SIT_RIGHT, ID_ANI_MARIO_TAIL_SIT_LEFT,
			ID_ANI_MARIO_POWERUP_TO_TAIL_RIGHT, ID_ANI_MARIO_POWERUP_TO_TAIL_LEFT

		}
};

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DebugOut(L"dt = %d\n", dt);
	vy += ay * dt;
	vx += ax * dt;

	if (isPickUp) {
		PickingItem(dt);
	}
	else {
		if (item != nullptr) {
			ReleaseItem(item);
			item = nullptr;
		}
	}

	if (abs(vx) > abs(maxVx)) vx = maxVx;


	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	// Stop recovering if time is up
	if (GetTickCount64() - recovery_start > MARIO_RECOVERY_TIME)
	{
		recovery_start = 0;
		isRecovering = 0;
	}
	if (isPowerUp
		|| GetTickCount64() - anchor_start < MARIO_DELAY_TIME_WHILE_ANCHOR_ON_AIR) {
		vy = 0.f;
		return;
	}
	preNx = nx;

	CCollision::GetInstance()->Process(this, dt, coObjects);
	//int x = mapAniId[0][0];
}

void CMario::OnNoCollision(DWORD dt)
{

	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<Koopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<Venus*>(e->obj))
		OnCollisionWithVenus(e);
	else if (dynamic_cast<VenusBullet*>(e->obj))
		OnCollisionWithFireBall(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<SpawnEnemy*> (e->obj))
		OnCollisionWithSpawnGate(e);
	else if (dynamic_cast<GoldBrick*>(e->obj))
	{
		if (dynamic_cast<GoldBrickWithButton*>(e->obj))
		{
			if (e->nx != 0)
			{
				GoldBrickWithButton* brick = dynamic_cast<GoldBrickWithButton*>(e->obj);
				brick->GotHit(e);
			}
		}
		GoldBrick* brick = dynamic_cast<GoldBrick*>(e->obj);
		if (e->ny > 0) // collision with top of brick
		{
			brick->GotHit(e);
		}
	}
	else if (dynamic_cast<Button*>(e->obj))
	{
		Button* button = dynamic_cast<Button*>(e->obj);
		button->GetPress();
	}
	else if (dynamic_cast<DropLift*>(e->obj))
	{
		DropLift* dropLift = dynamic_cast<DropLift*>(e->obj);
		if (e->ny < 0)
			dropLift->Touch();
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != CGoomba::DIE)
		{
			goomba->KickedFromTop(this);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != CGoomba::DIE)
			{
				DecreaseLevel();
			}
		}
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	Koopa* koopa = dynamic_cast<Koopa*>(e->obj);

	if (isPickUp)
		if (item == koopa) return;

	// jump on top >> kill Koopa and deflect a bit 
	if (e->ny < 0)
	{
		if (koopa->GetState() != Koopa::KNOCK_OUT)
		{
			koopa->KickedFromTop(this);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		DebugOut(L"Koopa, Mario hit by Koopa\n");
	}
	else if (e->ny > 0) {

		float Kvx, Kvy;
		koopa->GetSpeed(Kvx, Kvy);
		if (abs(Kvx) <= 0)
		{
			// koopa is in shell
			if (koopa->GetState() == Koopa::IN_SHELL_DOWN
				|| koopa->GetState() == Koopa::IN_SHELL_UP)
			{
				//These's make game knows M will Kick or hold
				if (this->GetState() == MARIO_STATE_RUNNING_LEFT
					|| this->GetState() == MARIO_STATE_RUNNING_RIGHT)
				{
					untouchable = 1;
					isPickUp = true;
					this->item = koopa;
					//koopa->WasPickedUp(this);
				}
				// Koopa git kicked by Mario
				else
				{
					float Mx, My, Kx, Ky;
					this->GetPosition(Mx, My);
					koopa->GetPosition(Kx, Ky);
					if (Mx - Kx >= 0)
						koopa->MoveInShell(1);
					else
						koopa->MoveInShell(-1);
				}
			}
		}
		// moving so 100% deal damege
		else
		{
			if (koopa->GetState() != Koopa::KNOCK_OUT)
			{
				DecreaseLevel();
			}
		}

	}
	else // colli with return value is x > 0 or x < 0
	{
		float Kvx, Kvy;
		koopa->GetSpeed(Kvx, Kvy);
		if (abs(Kvx) <= 0)
		{

			if (koopa->GetState() == Koopa::IN_SHELL_DOWN
				|| koopa->GetState() == Koopa::IN_SHELL_UP)
			{

				if (this->GetState() == MARIO_STATE_RUNNING_LEFT
					|| this->GetState() == MARIO_STATE_RUNNING_RIGHT)
				{
					untouchable = 1;
					isPickUp = true;
					this->item = koopa;
					//koopa->WasPickedUp(this);
				}

				else {
					if (nx >= 0)
						koopa->MoveInShell(1);
					else
						koopa->MoveInShell(-1);
				}

			}

		}
		else
		{
			if (untouchable == 0 && !isPickUp)
			{
				if (koopa->GetState() != Koopa::KNOCK_OUT)
				{
					DecreaseLevel();
				}
			}
		}
	}
}

void CMario::OnCollisionWithVenus(LPCOLLISIONEVENT e)
{
	if (untouchable == 0) {
		DecreaseLevel();
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* brick = dynamic_cast<CQuestionBrick*>(e->obj);
	if (e->ny > 0) // collision with top of brick
	{
		brick->GotHit((LPCOLLISIONEVENT)this);
	}
}
void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	//CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
	if (level == MARIO_LEVEL_SMALL)
	{
		GameManager::GetInstance()->AddScore(1000);
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
		SetLevel(MARIO_LEVEL_BIG);
		SetPowerUP(true);
		//SetSelfPausing(true);
		e->obj->Delete();
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		GameManager::GetInstance()->AddScore(1000);
		SetLevel(MARIO_LEVEL_TAIL);
		SetPowerUP(true);
		//SetSelfPausing(true);
		e->obj->Delete();
	}
	else 
	{
		GameManager::GetInstance()->AddScore(1000);
		DebugOut(L"Score ++\n");
		e->obj->Delete();
	}
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	if (level == MARIO_LEVEL_SMALL)
	{
		GameManager::GetInstance()->AddScore(1000);
		SetLevel(MARIO_LEVEL_BIG);
		SetPowerUP(true);
		e->obj->Delete();
	}
	else
	{
		GameManager::GetInstance()->AddScore(1000);
		DebugOut(L"Score ++\n");
		e->obj->Delete();
	}
}
void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e)
{
	if (untouchable == 0) {
		DecreaseLevel();
		//e->obj->Delete();
	}
}

void CMario::OnCollisionWithSpawnGate(LPCOLLISIONEVENT e)
{
	SpawnEnemy* spawnGate = dynamic_cast<SpawnEnemy*>(e->obj);
	spawnGate->TouchedByMario();
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

int CMario::ConvertAniTypeToAniId(int animation_type)
{
	return mapAniId[this->level - 1][animation_type];
}

//
// Get animdation ID for big Mario
//
int CMario::GetAniId()
{
	int aniId = -1;

	if (isPowerUp)
	{
		if (nx >= 0)
			aniId = ConvertAniTypeToAniId(ANI_MARIO_POWER_UP_RIGHT);
		else
			aniId = ConvertAniTypeToAniId(ANI_MARIO_POWER_UP_LEFT);
		return aniId;
	}//early return at here to focus on animation
	if (isSitting) // this case is sitting
	{
		if (nx >= 0)
			aniId = ConvertAniTypeToAniId(ANI_MARIO_SIT_RIGHT);
		else
			aniId = ConvertAniTypeToAniId(ANI_MARIO_SIT_LEFT);
		return aniId;
	}

	if (!isOnPlatform) // this case is Jump/fall out
	{
		if (isPickUp) // jump and holding item
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ConvertAniTypeToAniId(ANI_MARIO_PICKING_RUN_JUMP_RIGHT);
				else
					aniId = ConvertAniTypeToAniId(ANI_MARIO_PICKING_RUN_JUMP_LEFT);
			}
			else
			{
				if (nx >= 0)
					aniId = ConvertAniTypeToAniId(ANI_MARIO_PICKING_JUMP_RIGHT);
				else
					aniId = ConvertAniTypeToAniId(ANI_MARIO_PICKING_JUMP_LEFT);
			}
		}
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_JUMP_RUN_RIGHT);
			else
				aniId = ConvertAniTypeToAniId(ANI_MARIO_JUMP_RUN_LEFT);
		}
		else
		{
			if (nx >= 0)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_JUMP_WALK_RIGHT);
			else
				aniId = ConvertAniTypeToAniId(ANI_MARIO_JUMP_WALK_LEFT);
		}
	}
	else if (isPickUp) // this case is Pick the Koopa
	{
		if (abs(vx) > MARIO_WALKING_SPEED)
		{
			if (nx >= 0)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_PICKING_RUN_RIGHT);
			else
				aniId = ConvertAniTypeToAniId(ANI_MARIO_PICKING_RUN_LEFT);
		}
		else if (abs(vx) > 0)
		{
			if (nx >= 0)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_PICKING_WALK_RIGHT);
			else
				aniId = ConvertAniTypeToAniId(ANI_MARIO_PICKING_WALK_LEFT);
		}
		else
		{
			if (nx >= 0)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_PICKING_IDLE_RIGHT);
			else
				aniId = ConvertAniTypeToAniId(ANI_MARIO_PICKING_IDLE_LEFT);
		}
	}
	else //  another movement
	{
		if (vx > 0)
		{
			if (ax < 0 && state != MARIO_STATE_IDLE)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_BRACE_RIGHT);
			else if (ax < 0 && state == MARIO_STATE_IDLE)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_WALKING_RIGHT);
			else if (ax == MARIO_ACCEL_RUN_X)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_RUNNING_RIGHT);
			else if (ax == MARIO_ACCEL_WALK_X)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_WALKING_RIGHT);
		}
		else if (vx < 0)
		{
			if (ax > 0 && state != MARIO_STATE_IDLE)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_BRACE_LEFT);
			else if (ax > 0 && state == MARIO_STATE_IDLE)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_WALKING_LEFT);
			else if (ax == -MARIO_ACCEL_RUN_X)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_RUNNING_LEFT);
			else if (ax == -MARIO_ACCEL_WALK_X)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_WALKING_LEFT);
		}
		else
		{
			if (nx >= 0)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_IDLE_RIGHT);
			else
				aniId = ConvertAniTypeToAniId(ANI_MARIO_IDLE_LEFT);
		}


	}


	if (aniId == -1) aniId = ConvertAniTypeToAniId(ANI_MARIO_IDLE_RIGHT);

	return aniId;
}


void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else
		aniId = GetAniId();

	//there is some case will overlap prev animation in game loop. 
	//render while after got hit (I/We call it is recovery state-but not actually state bruh)
	if (isRecovering)
	{
		if (((GetTickCount64() - recovery_start) % MARIO_HIDDEN_GAP_WHILE_RECOVERY) >= MARIO_HIDDEN_GAP_WHILE_RECOVERY / 2) return;
	}
	//render while isPowerUp got a new anim 
	if (isPowerUp) {
		if (animations->Get(aniId)->Done()) {
			isPowerUp = false;
			animations->Get(aniId)->Reset();
			GameManager::GetInstance()->SetPausedToTransform(false);
		}
	}
	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();

	//DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		//if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	case MARIO_STATE_SMALL_JUMP:
		//if (isSitting) break;
		if (isOnPlatform)
		{
			vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			isPickUp = false;
			//vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
			if (vx * (vx + ax * 14) <= 0) {
				vx = 0.0f;
				ax = 0.0f;
			}
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		if (abs(vx) >= MARIO_WALKING_SPEED)
		{
			if (vx >= 0)
			{
				ax = -MARIO_ACCEL_RUN_X;
			}
			else
			{
				ax = MARIO_ACCEL_RUN_X;
			}
		}
		else if (abs(vx) > 0) {
			if (vx >= 0)
				ax = -MARIO_ACCEL_WALK_X;
			else
				ax = MARIO_ACCEL_WALK_X;
		}
		if (vx * (vx + ax * 14) <= 0) {
			vx = 0.0f;
			ax = 0.0f;
		}

		break;


	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}


	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_TAIL)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}
void CMario::DecreaseLevel()
{
	if (level == MARIO_LEVEL_SMALL) {
		SetState(MARIO_STATE_DIE);
	}
	else
	{
		level -= 1;
		StartUntouchable();
		StartRecovery();
	}
}

void CMario::PickingItem(DWORD dt) {
	if (this->item == nullptr || this->item->IsDeleted()) {
		//ReleaseItem(item);
		return;
	}
	float fdt = (float)dt;

	if (dynamic_cast<Koopa*>(item))
	{
		Koopa* koopa = dynamic_cast<Koopa*>(item);
		koopa->SetHolded(true);

		//IF YOU READ THIS LINE "BẠN ĐÃ BỊ CON MÈO"
		//if (preNx * nx <= 0) {
		//	item->SetPosition(this->x + 16 * nx, this->y);
		//}
		//float tempVy = 0;
		//if (!isOnPlatform) {
		//	tempVy = this->vy;
		//	DebugOut(L"SET temp %f", tempVy);
		//}
		//DebugOut(L"SEEE temp %f", tempVy);
		//item->SetSpeed(this->vx, tempVy);

		float targetX = x + 16 * nx + (this->vx * fdt), targetY = y + (this->vy * fdt);
		float curX, curY;
		item->GetPosition(curX, curY);
		float kVx = (targetX - curX) / (float)fdt, kVy = (targetY - curY) / (float)fdt;
		item->SetSpeed(kVx, kVy);
		koopa->SetAccelation(0, 0);

		if (koopa->IsTimeOut())
		{
			isPickUp = false;
		}
	}

}
void CMario::ReleaseItem(CGameObject* item) {
	if (item == nullptr || item->IsDeleted()) {
		return;
	}
	Koopa* koopa = dynamic_cast<Koopa*> (item);
	if (koopa == nullptr) return;

	koopa->SetHolded(false);
	koopa->SetAccelation(0.f, KOOPA_GRAVITY);
	koopa->ReleaseByPlayer(this);
	//this->item = nullptr;
}