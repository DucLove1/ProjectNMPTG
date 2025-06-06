#include <algorithm>
#include "debug.h"

#include "SampleKeyEventHandler.h"
#include "Mario.h"
#include "MarioTail.h"
#include "Game.h"

#include "Pipe.h"
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
#include "PlayScene.h"
#include "DropLift.h"
#include "ComboScoreSystemMario.h"
#include "RandomCard.h"
#include "GameClock.h"
#include "BoomerangBro.h"
#include "PiranhaPlant.h"
//define for Id map
int mapAniId[][35] = {
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
			ID_ANI_MARIO_SMALL_IDLE_RIGHT, ID_ANI_MARIO_SMALL_IDLE_LEFT, // fill array with idle (this is powerUp)
			ID_ANI_MARIO_SMALL_IDLE_RIGHT, ID_ANI_MARIO_SMALL_IDLE_LEFT, // fill array with idle (this is slowfalling)
			ID_ANI_MARIO_SMALL_IDLE_RIGHT, ID_ANI_MARIO_SMALL_IDLE_LEFT, // fill array with idle (this is attacking)
			ID_ANI_MARIO_SMALL_IDLE_RIGHT, ID_ANI_MARIO_SMALL_IDLE_LEFT,  // fill array with idle (this is flying)
			ID_ANI_MARIO_SMALL_KICKING_RIGHT, ID_ANI_MARIO_SMALL_KICKING_LEFT,
			ID_ANI_MARIO_SMALL_ENTRY_PIPE
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
			ID_ANI_MARIO_SMALL_TO_BIG_RIGHT,ID_ANI_MARIO_SMALL_TO_BIG_LEFT,
			ID_ANI_MARIO_IDLE_RIGHT, ID_ANI_MARIO_IDLE_LEFT,// fill array with idle (this is slowfalling)
			ID_ANI_MARIO_IDLE_RIGHT, ID_ANI_MARIO_IDLE_LEFT,// fill array with idle (this is attacking)
			ID_ANI_MARIO_IDLE_RIGHT, ID_ANI_MARIO_IDLE_LEFT,// fill array with idle (this is flying)
			ID_ANI_MARIO_KICKING_RIGHT, ID_ANI_MARIO_KICKING_LEFT,
			ID_ANI_MARIO_BIG_ENTRY_PIPE
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
			ID_ANI_MARIO_POWERUP_TO_TAIL_RIGHT, ID_ANI_MARIO_POWERUP_TO_TAIL_LEFT,
			ID_ANI_MARIO_TAIL_SLOWFALLING_RIGHT, ID_ANI_MARIO_TAIL_SLOWFALLING_LEFT,
			ID_ANI_MARIO_TAIL_ATTACK_RIGHT, ID_ANI_MARIO_TAIL_ATTACK_LEFT,
			ID_ANI_MARIO_FLY_RIGHT, ID_ANI_MARIO_FLY_LEFT,
			ID_ANI_MARIO_TAIL_KICK_RIGHT, ID_ANI_MARIO_TAIL_KICK_LEFT,
			ID_ANI_MARIO_TAIL_ENTRY_PIPE,
		}
};

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isEndGame) {
		UpdateWhenEndScene(dt, coObjects);
		return;
	}
	if (isPrepareEntry) {
		UpdateWhenPrepareEntry(dt, coObjects);
		return;
	}
	if (isEntryPipe) {
		UpdateWhenEntryPipe(dt, coObjects);
		return;
	}
	if (isExitPipe)
	{
		UpdateWhenExitPipe(dt, coObjects);
		return;
	}

	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	if (GetState() == MARIO_STATE_RUNNING_LEFT
		|| GetState() == MARIO_STATE_RUNNING_RIGHT
		|| GetState() == MARIO_STATE_JUMP)
	{
		if (abs(vy) > 0.5f)
			vy = 0.5f * vy / abs(vy);
	}
	else
	{
		if (abs(vy) > 0.3f)
			vy = 0.3f * vy / abs(vy);
	}

	if (state == MARIO_STATE_IDLE || state == MARIO_STATE_SIT)
	{
		if (vx * nx < 0) vx = ax = 0;
		if (vy <= -MARIO_JUMP_SPEED_Y)
		{
			if (ay != 0) ay = 0;
		}
	}
	// Jumping logic
	if (vy < 0) {
		if (jumpedTime < MARIO_MAX_JUMP_TIME) {
			jumpedTime += dt;
			if (jumpedTime >= MARIO_MAX_JUMP_TIME / 2)
				ay = 0;
			if (jumpedTime >= MARIO_MAX_JUMP_TIME)
				ay = MARIO_GRAVITY;
		}
	}

	if (GetState() == MARIO_STATE_RUNNING_LEFT
		|| GetState() == MARIO_STATE_RUNNING_RIGHT)
	{
		if (!isFlying && !isSlowFalling)
		{
			powerUnit += dt * 2.5f;
			if (powerUnit >= MAX_POWER_UNIT)
			{
				powerUnit = MAX_POWER_UNIT;
			}
		}
	}
	else if (!(state == MARIO_STATE_RELEASE_JUMP) && !isFlying)
	{
		powerUnit -= dt * 10.0f;
		if (powerUnit < 0.0f)
		{
			powerUnit = 0.0f;
		}
	}
	if (isFlying)
	{
		if (GameClock::GetInstance()->GetTime() - startFlying > 5000.0f)
		{
			startFlying = 0;
			powerUnit = 0;
		}
	}
	GameManager::GetInstance()->SetPower(powerUnit / (MAX_POWER_UNIT / 7));
	/*if (GameClock::GetInstance()->GetTime() % 10 % 2 == 1)
	{
		DebugOut(L"%d	", IsReadyToFly());
		DebugOut(L"Power Unit : %f \n", powerUnit);
		DebugOut(L"startFlying : %f \n", startFlying);
	}*/
	//DebugOut(L"Power Unit : %f \n", powerUnit);

	if (flyingTime > 0)
	{
		vy = MARIO_JUMP_SPEED_Y * FLYING_SCALE;
		//vy = MARIO_ACCEL_JUMP * (MARIO_MAX_JUMP_IME / (float)dt) * FLYING_SCALE;
		flyingTime -= dt;
		ay = 0;
	}
	else if (flyingTime <= 0 && isFlying)
	{
		jumpedTime = MARIO_MAX_JUMP_TIME + 1; // reset jumped time
		//SetState(MARIO_STATE_RELEASE_JUMP); // reset state to idle
		ay = MARIO_GRAVITY;
		isFlying = false;
		//DebugOut(L"DONE");
	}

	if (slowFallingTime > 0)
	{
		vy = MARIO_JUMP_SPEED_Y * SLOW_FALLING_SCALE;
		slowFallingTime -= dt;
		//tailFlapAnimationCurrentDuration -= dt;
	}
	else if (slowFallingTime <= 0 && isSlowFalling)
	{
		jumpedTime = MARIO_MAX_JUMP_TIME + 1; // reset jumped time
		//vy = MARIO_JUMP_SPEED_Y;

		isSlowFalling = false;

	}


	// reset untouchable timer if untouchable time has passed
	if (GameClock::GetInstance()->GetTime() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	// Stop recovering if time is up
	if (GameClock::GetInstance()->GetTime() - recovery_start > MARIO_RECOVERY_TIME)
	{
		recovery_start = 0;
		isRecovering = 0;
	}
	if (isPowerUp)
	{
		nx = preNx;
		SetState(MARIO_STATE_SIT_RELEASE); // reset state to idle
		return;
	}
	else
		if ((GetTickCount64() - anchor_start < MARIO_DELAY_TIME_WHILE_ANCHOR_ON_AIR && GetLevel() == MARIO_LEVEL_BIG)
			|| (GetTickCount64() - anchor_start < MARIO_DELAY_TIME_WHILE_ANCHOR_ON_AIR_TAIL && GetLevel() == MARIO_LEVEL_TAIL))
		{
			vy = 0.0f;
			vx = 0.0f;
		}

	if (GetLevel() != MARIO_LEVEL_TAIL)
	{
		SetAttack(false);
	}
	else if (IsAttack())
	{
		nx = preNx;
	}



	if (movingPlatform != nullptr) {
		float dl_vx, dl_vy;
		movingPlatform->GetSpeed(dl_vx, dl_vy);
		float dl_left, dl_top, dl_right, dl_bottom;
		movingPlatform->GetBoundingBox(dl_left, dl_top, dl_right, dl_bottom);

		if (dl_vx < 0 && vx > dl_vx)
		{
			vx = dl_vx;
		}
		else if (dl_vx > 0 && vx < dl_vx)
		{
			vx = dl_vx;
		}

		if (dl_vy > 0 && vy > 0) {
			float halfHeight = (this->GetLevel() == MARIO_LEVEL_SMALL) ? (MARIO_SMALL_BBOX_HEIGHT / 2.0f) : (MARIO_BIG_BBOX_HEIGHT / 2.0f);
			float target_y = dl_top - halfHeight;
			vy = (target_y - y) / dt;
		}
	}

	DebugOut(L"MAX %f %f\n", x, y);
	//if (abs(vx) > abs(maxVx)) vx = maxVx;

	preNx = nx;
	this->fdt = (float)dt;

	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (isPickUp) {
		PickingItem(dt);
	}
	else {
		if (item != nullptr) {
			ReleaseItem(item);
			item = nullptr;
		}
	}

	UpdateTail(dt);


	LimitByCameraBorder();
	//limit top map 1 
	if (x < -350.0f) x = -350.0f;
}

void CMario::UpdateWhenEndScene(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(MARIO_STATE_ENDGAME);
	vx += ax * dt;
	vy += ay * dt;
	if (abs(vx) > abs(maxVx)) vx = maxVx;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::UpdateWhenEntryPipe(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	SetState(MARIO_STATE_ENTRY_PIPE);

	float ny = 0.0f;

	if (isEntryDown == true)
	{
		ny = 1.0f;
	}
	else
	{
		ny = -1.0f;
	}


	this->vy = MARIO_SPEED_ENTRY_PIPE * ny;
	//DebugOut(L"this is ny %f %f \n", ny, vy);

	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CMario::UpdateWhenPrepareEntry(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//if (this->state != MARIO_STATE_PREPARE_ENTRY_PIPE) 
	//{
	//	DebugOut(L"RETURN THIS \n");
	//	return;
	//}	
	//SetState(MARIO_STATE_PREPARE_ENTRY_PIPE);

	vx = (this->targetPoint.first - this->x) / dt; //moving target point
	vx /= 25;
	if (vx >= 0)
	{
		SetSpeed(max(vx, 0.005), 0.0f); // set speed to target point
	}
	else
	{
		SetSpeed(min(vx, -0.005), 0.0f);
	}
	if (vx >= 0) nx = 1;
	else nx = -1;
	//if (abs(vx) > abs(maxVx)) vx = maxVx; // limit max speed

	CCollision::GetInstance()->Process(this, dt, coObjects);
	//preVx = vx;
	//DebugOut(L"Prepare Entry Pipe: %f, %f\n", this->targetPoint.first - this->x, vx);

	//if (vx * preVx <= 0.0f)
	if (abs(this->targetPoint.first - this->x) <= 0.1)
	{
		SetState(MARIO_STATE_ENTRY_PIPE); // change state to entry pipe
		//DebugOut(L"Checked\n");
	}
}
void CMario::UpdateWhenExitPipe(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float addedHeight =
		((GetLevel() == MARIO_LEVEL_SMALL) ?
			(MARIO_SMALL_BBOX_HEIGHT) : (MARIO_BIG_BBOX_HEIGHT)) * directionToExit;

	float YTarget = startPoint.second + addedHeight;

	vy = (YTarget - this->y) / dt; //moving target point
	vy /= 20.0f;
	if (vy >= 0.0f)
	{
		SetSpeed(0.0f, max(vy, 0.01f)); // set speed to target point
	}
	else
	{
		SetSpeed(0.0f, min(vy, -0.01f));
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (directionToExit > 0.0f && this->y >= YTarget)
	{
		isExitPipe = false;
		SetState(MARIO_STATE_RELEASE_JUMP);
	}
	else if (directionToExit < 0.0f && YTarget >= this->y)
	{
		isExitPipe = false;
		SetState(MARIO_STATE_RELEASE_JUMP);
	}

	/*if (abs(YTarget - this->y) <= 0.02f)
	{
		isExitPipe = false;
		SetState(MARIO_STATE_RELEASE_JUMP);
	}*/
	DebugOut(L"%f %f \n", YTarget, this->y);
}

void CMario::OnNoCollision(DWORD dt)
{
	//SetLinked(false, false); // reset linked state

	x += vx * dt;
	y += vy * dt;

	if (!isLinked)
		isOnPlatform = false;

}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CPipe*>(e->obj))
		OnCollisionWithPipe(e);
	else
		canEntryPipe = false;

	if (e->ny != 0 && e->obj->IsBlocking())
	{
		if (e->ny < 0)
		{
			vy = 0;
			isOnPlatform = true;
			slowFallingTime = 0;
			flyingTime = 0;
			// reset streak score when Mario lands on the ground
			ComboScoreSystemMario::GetInstance()->Reset();
		}
		else {
			jumpedTime = MARIO_MAX_JUMP_TIME - 1;
			vy = -0.001f;
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		if (!isFlying)
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
		OnCollisionWithGoldBrick(e);
	else if (dynamic_cast<Button*>(e->obj))
	{
		Button* button = dynamic_cast<Button*>(e->obj);
		button->GetPress();
	}
	else if (dynamic_cast<DropLift*>(e->obj))
		OnColliionWithDropLift(e);
	else if (dynamic_cast<RandomCard*>(e->obj))
	{
		RandomCard* randomCard = dynamic_cast<RandomCard*>(e->obj);
		randomCard->Touched();
		this->SetForEndGame(true);
	}
	else if (dynamic_cast<BoomerangBro*>(e->obj))
		OnCollisionWithBoomerangBro(e);
	else if (dynamic_cast<PiranhaPlant*>(e->obj))
	{
		OnCollisionWithPiranhaPlant(e);
	}
	//else
	//	SetLinked(false, false); // reset linked state

}

void CMario::OnCollisionWithPipe(LPCOLLISIONEVENT e)
{
	CPipe* pipe = dynamic_cast<CPipe*>(e->obj);
	if (pipe != nullptr && e->ny < 0 && !isPrepareEntry && !isEntryPipe)
	{

		canEntryPipe = true;
		pipe->GetPosition(targetPoint.first, targetPoint.second); // get target point of pipe
		pipe->SetEntryPipe(true); // set pipe to entry state
	}
	else if (pipe != nullptr && e->ny > 0)// && upArrowWasHolded)
	{
		canEntryPipe = true;
		pipe->GetPosition(targetPoint.first, targetPoint.second);
		pipe->SetEntryPipe(true);
		if (abs(targetPoint.first - this->x) >= MARIO_BIG_BBOX_WIDTH / 3) return;
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->IsAlive())
		{
			goomba->KickedFromTop(this);
			if (this->IsSlowFalling())
			{
				SetSlowFalling(false);
				slowFallingTime = 0.0f;
				cdSlowFallingByDIK_X = 4.0f;
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->IsAlive())
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
			if (this->IsSlowFalling())
			{
				SetSlowFalling(false);
				slowFallingTime = 0.0f;
				cdSlowFallingByDIK_X = 4.0f;
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		//DebugOut(L"Koopa, Mario hit by Koopa\n");
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
				//if (this->GetState() == MARIO_STATE_RUNNING_LEFT
				//	|| this->GetState() == MARIO_STATE_RUNNING_RIGHT)
				if (KeyAWasHoled())
				{
					untouchable = 1;
					isPickUp = true;
					this->item = koopa;
					//koopa->WasPickedUp(this);
				}
				// Koopa got kicked by Mario
				else
				{
					startReleaseItem = GameClock::GetInstance()->GetTime();
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

				//if (this->GetState() == MARIO_STATE_RUNNING_LEFT
				//	|| this->GetState() == MARIO_STATE_RUNNING_RIGHT)
				if (KeyAWasHoled())
				{
					untouchable = 1;
					isPickUp = true;
					this->item = koopa;
					//koopa->WasPickedUp(this);
				}

				else {
					startReleaseItem = GameClock::GetInstance()->GetTime();
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
	GameManager::GetInstance()->PlusCoins(1);
	GameManager::GetInstance()->AddScore(50);
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
	CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
	if (level == MARIO_LEVEL_SMALL)
	{
		//GameManager::GetInstance()->AddScore(1000);
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
		SetLevel(MARIO_LEVEL_BIG);
		SetPowerUP(true);
		//SetSelfPausing(true);
		//e->obj->Delete();
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		//GameManager::GetInstance()->AddScore(1000);
		SetLevel(MARIO_LEVEL_TAIL);
		SetPowerUP(true);
		//SetSelfPausing(true);
		//e->obj->Delete();
	}
	else
	{
		//GameManager::GetInstance()->AddScore(1000);
		//DebugOut(L"Score ++\n");
		//e->obj->Delete();
	}
	if (leaf)
		leaf->Touched(); // leaf will be deleted after touched
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	mushroom->Touched();
	if (level == MARIO_LEVEL_SMALL)
	{
		//GameManager::GetInstance()->AddScore(1000);
		SetLevel(MARIO_LEVEL_BIG);
		SetPowerUP(true);
		//e->obj->Delete();
	}
	else
	{
		//GameManager::GetInstance()->AddScore(1000);
		DebugOut(L"Score ++\n");
		//e->obj->Delete();
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

void CMario::OnCollisionWithGoldBrick(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<GoldBrickWithButton*>(e->obj))
	{
		if (e->ny > 0)
		{
			GoldBrickWithButton* brick = dynamic_cast<GoldBrickWithButton*>(e->obj);
			brick->GotHit(e);
		}
		else return;
	}
	GoldBrick* brick = dynamic_cast<GoldBrick*>(e->obj);
	if (brick) // collision with top of brick
	{
		brick->GotHit(e);
	}
}

void CMario::OnColliionWithDropLift(LPCOLLISIONEVENT e)
{
	DropLift* dropLift = dynamic_cast<DropLift*>(e->obj);
	dropLift->OnCollidedWithMario(e);
}

void CMario::OnCollisionWithBoomerangBro(LPCOLLISIONEVENT e)
{
	BoomerangBro* boomerangBro = dynamic_cast<BoomerangBro*>(e->obj);
	if (e->ny < 0)
	{
		if (boomerangBro->IsAlive())
		{
			boomerangBro->KickedFromTop(this);
			if (this->IsSlowFalling())
			{
				SetSlowFalling(false);
				slowFallingTime = 0.0f;
				cdSlowFallingByDIK_X = 4.0f;
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (boomerangBro->IsAlive())
			{
				DecreaseLevel();
			}
		}
	}
}

void CMario::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
	PiranhaPlant* piranhaPlant = dynamic_cast<PiranhaPlant*>(e->obj);
	if (!piranhaPlant)
		return;
	if (piranhaPlant->IsAlive())
	{
		if (untouchable == 0)
			DecreaseLevel();
	}

}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	//CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
	// write the out pos
	float x, y;
	p->GetPosOut(x, y);
	CGame::GetInstance()->GetCurrentScene()->SetPosOut(x, y);
	p->SwitchScene();
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
	//render while attacking
	if (IsAttack())
	{
		if (nx >= 0)
			aniId = ConvertAniTypeToAniId(ANI_MARIO_ATTACK_RIGHT);
		else
			aniId = ConvertAniTypeToAniId(ANI_MARIO_ATTACK_LEFT);
		return aniId;
	}
	if (isPrepareEntry)
	{
		if (nx >= 0)
			aniId = ConvertAniTypeToAniId(ANI_MARIO_WALKING_RIGHT);
		else
			aniId = ConvertAniTypeToAniId(ANI_MARIO_WALKING_LEFT);
		return aniId;
	}

	if (isEntryPipe || isExitPipe)
	{
		aniId = ConvertAniTypeToAniId(ANI_MARIO_ENTRY_PIPE);
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
		else if (isFlying)
		{
			if (nx >= 0)
			{
				aniId = ConvertAniTypeToAniId(ANI_MARIO_FLYING_RIGHT);
			}
			else
			{
				aniId = ConvertAniTypeToAniId(ANI_MARIO_FLYING_LEFT);
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

		if (isSlowFalling) // this case is slow falling
		{
			if (nx >= 0)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_SLOWFALLING_RIGHT);
			else
				aniId = ConvertAniTypeToAniId(ANI_MARIO_SLOWFALLING_LEFT);
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
	else if (GameClock::GetInstance()->GetTime() - startReleaseItem < 150)
	{
		if (preNx != nx) startReleaseItem = 0;
		if (nx >= 0)
			aniId = ConvertAniTypeToAniId(ANI_MARIO_KICK_RIGHT);
		else
			aniId = ConvertAniTypeToAniId(ANI_MARIO_KICK_LEFT);
	}
	else //  another movement
	{
		if (vx > 0)
		{
			if (ax < 0 && state != MARIO_STATE_IDLE)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_BRACE_RIGHT);
			else if (ax < 0 && state == MARIO_STATE_IDLE)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_WALKING_RIGHT);
			else if (IsMAXRunning())//(ax == MARIO_ACCEL_RUN_X)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_RUNNING_RIGHT);
			else if (ax >= MARIO_ACCEL_WALK_X)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_WALKING_RIGHT);
		}
		else if (vx < 0)
		{
			if (ax > 0 && state != MARIO_STATE_IDLE)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_BRACE_LEFT);
			else if (ax > 0 && state == MARIO_STATE_IDLE)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_WALKING_LEFT);
			else if (IsMAXRunning())//(ax == -MARIO_ACCEL_RUN_X)
				aniId = ConvertAniTypeToAniId(ANI_MARIO_RUNNING_LEFT);
			else if (ax <= MARIO_ACCEL_WALK_X)
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
		if (((GameClock::GetInstance()->GetTime() - recovery_start) % MARIO_HIDDEN_GAP_WHILE_RECOVERY) >= MARIO_HIDDEN_GAP_WHILE_RECOVERY / 2) return;
	}
	//render while isPowerUp got a new anim 
	if (isPowerUp) {
		if (animations->Get(aniId)->Done()) {
			isPowerUp = false;
			animations->Get(aniId)->Reset();
			GameManager::GetInstance()->SetPausedToTransform(false);
		}
	}
	//Fix: sometime it's will be wrong if it not to reset
	if (!IsAttack())
	{
		animations->Get(ID_ANI_MARIO_TAIL_ATTACK_LEFT)->Reset();
		animations->Get(ID_ANI_MARIO_TAIL_ATTACK_RIGHT)->Reset();
	}

	if (isPrepareEntry || isEntryPipe || isExitPipe)
	{
		return;
	}
	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();

	//DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{

	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	{
		//switch (state)
		//{
		//case MARIO_STATE_RUNNING_RIGHT:
		//	if (isSitting) break;
		//	maxVx = MARIO_RUNNING_SPEED;
		//	ax = MARIO_ACCEL_RUN_X;
		//	nx = 1;
		//	break;
		//case MARIO_STATE_RUNNING_LEFT:
		//	if (isSitting) break;
		//	maxVx = -MARIO_RUNNING_SPEED;
		//	ax = -MARIO_ACCEL_RUN_X;
		//	nx = -1;
		//	break;
		//case MARIO_STATE_WALKING_RIGHT:
		//	if (isSitting) break;
		//	maxVx = MARIO_WALKING_SPEED;
		//	ax = MARIO_ACCEL_WALK_X;
		//	nx = 1;
		//	break;
		//case MARIO_STATE_WALKING_LEFT:
		//	if (isSitting) break;
		//	maxVx = -MARIO_WALKING_SPEED;
		//	ax = -MARIO_ACCEL_WALK_X;
		//	nx = -1;
		//	break;
		//case MARIO_STATE_JUMP:
		//	//if (isSitting) break;
		//	if (isOnPlatform)
		//	{
		//		if (abs(this->vx) == MARIO_RUNNING_SPEED)
		//			vy = -MARIO_JUMP_RUN_SPEED_Y;
		//		else
		//			vy = -MARIO_JUMP_SPEED_Y;
		//	}
		//	break;
		//case MARIO_STATE_SMALL_JUMP:
		//	//if (isSitting) break;
		//	if (isOnPlatform)
		//	{
		//		vy = -MARIO_JUMP_SPEED_Y;
		//	}
		//	break;
		//case MARIO_STATE_RELEASE_JUMP:
		//	if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		//	break;
		//case MARIO_STATE_SLOW_FALLING:
		//	isSlowFalling = true;
		//	if (isSlowFalling)
		//	{
		//		CAnimations* animations = CAnimations::GetInstance(); 
		//		
		//		if (animations->Get(GetAniId())->Done())
		//		{
		//			isSlowFalling = false;
		//		}
		//		else
		//		{
		//			vy -= MARIO_GRAVITY;
		//			if(vy <= MARIO_MAX_FALLING_SPEED)
		//				vy = MARIO_MAX_FALLING_SPEED;
		//		}
		//	}
		//	break;
		//case MARIO_STATE_SIT:
		//	if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		//	{
		//		state = MARIO_STATE_IDLE;
		//		isSitting = true;
		//		isPickUp = false;
		//		//vx = 0; vy = 0.0f;
		//		y += MARIO_SIT_HEIGHT_ADJUST;
		//		if (vx * (vx + ax * 14) <= 0) {
		//			vx = 0.0f;
		//			ax = 0.0f;
		//		}
		//	}
		//	break;

		//case MARIO_STATE_SIT_RELEASE:
		//	if (isSitting)
		//	{
		//		isSitting = false;
		//		state = MARIO_STATE_IDLE;
		//		y -= MARIO_SIT_HEIGHT_ADJUST;
		//	}
		//	break;

		//case MARIO_STATE_IDLE:
		//	if (abs(vx) >= MARIO_WALKING_SPEED)
		//	{
		//		if (vx >= 0)
		//		{
		//			ax = -MARIO_ACCEL_RUN_X;
		//		}
		//		else
		//		{
		//			ax = MARIO_ACCEL_RUN_X;
		//		}
		//	}
		//	else if (abs(vx) > 0) {
		//		if (vx >= 0)
		//			ax = -MARIO_ACCEL_WALK_X;
		//		else
		//			ax = MARIO_ACCEL_WALK_X;
		//	}
		//	if (vx * (vx + ax * 14) <= 0) {
		//		vx = 0.0f;
		//		ax = 0.0f;
		//	}

		//	break;


		//case MARIO_STATE_DIE:
		//	vy = -MARIO_JUMP_DEFLECT_SPEED;
		//	vx = 0;
		//	ax = 0;
		//	break;
		//}
	}

	//CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting)
			SetState(MARIO_STATE_SIT_RELEASE);
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting)
			SetState(MARIO_STATE_SIT_RELEASE);
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting)
			SetState(MARIO_STATE_SIT_RELEASE);
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting)
			SetState(MARIO_STATE_SIT_RELEASE);
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (!isOnPlatform) break;

		if (abs(this->vx) == MARIO_RUNNING_SPEED)
			vy = -MARIO_JUMP_RUN_SPEED_Y;
		else
			ay = -MARIO_ACCEL_JUMP, jumpedTime = 0;

		if (abs(vx) > MARIO_WALKING_SPEED && abs(vx) < MARIO_RUNNING_SPEED)
			vx = MARIO_WALKING_SPEED * nx;

		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (jumpedTime > 0)
			jumpedTime = min(jumpedTime + MARIO_MAX_JUMP_TIME / 2, MARIO_MAX_JUMP_TIME - 1);
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL && !isSitting)
		{
			isSitting = true;
			vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
			SetState(MARIO_STATE_IDLE);
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
		ax = (-1) * nx * MARIO_FRICTION;
		break;


	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;

	case MARIO_STATE_PREPARE_ENTRY_PIPE:
		DisableAllAction();

		isPrepareEntry = true;
		y -= MARIO_SIT_HEIGHT_ADJUST;

		//isEntryPipe = false;
		//isSitting = false;
		//SetAttack(false);
		//isRecovering = false;
		//isPowerUp = false;
		//isPickUp = false;
		// 
		//vy = 0;
		//ax = 0;
		//ay = 0;

		maxVx = MARIO_SPEED_ENTRY_PIPE;

		//DebugOut(L" STATE Prepare Entry Pipe: %f, %f\n", targetPoint.first, targetPoint.second);
		break;

	case MARIO_STATE_ENTRY_PIPE:
		DisableAllAction();

		isEntryPipe = true;
		//isPrepareEntry = false;
		//isSitting = false;
		//SetAttack(false);
		//isRecovering = false;
		//isPowerUp = false;
		//isPickUp = false;
		//
		//maxVx = 0;
		//vx = 0;
		//ax = 0;
		//ay = 0;
		//DebugOut(L"STATE Entry Pipe: %f, %f\n",  this->vx, this->vy);
		break;

	case MARIO_STATE_EXIT_PIPE:
		DisableAllAction();
		isExitPipe = true;

		break;

	case MARIO_STATE_ENDGAME:
		isSitting = false;
		isPowerUp = false;
		isPickUp = false;
		isEntryPipe = false;
		isPrepareEntry = false;
		isExitPipe = false;
		SetAttack(false);
		isRecovering = false;
		isPowerUp = false;

		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		ay = MARIO_GRAVITY;
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


void CMario::LimitByCameraBorder()
{
	float camLeft, camTop, camRight, camBottom;

	CGame::GetInstance()->GetCamPos(camLeft, camTop);
	float camWidth = CGame::GetInstance()->GetBackBufferWidth();
	//float camHeight = CGame::GetInstance()->GetBackBufferHeight();

	camRight = camLeft + camWidth;
	//camBottom = camTop + camHeight;

	if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_TAIL)
	{
		camLeft += MARIO_BIG_BBOX_WIDTH / 2;
		camRight -= MARIO_BIG_BBOX_WIDTH / 2;
	}
	else
	{
		camLeft += MARIO_SMALL_BBOX_WIDTH / 2;
		camRight -= MARIO_SMALL_BBOX_WIDTH / 2;
	}
	// it's not acctually cameralimit, its border limit
	if (x < camLeft) x = camLeft;
	if (x > camRight) x = camRight;

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

		float targetX = x + 10 * nx; // +(this->vx * fdt);
		float targetY = y; //+ (this->vy * fdt);

		if (this->level == MARIO_LEVEL_SMALL)
		{
			targetX -= (16 / 2 - MARIO_SMALL_BBOX_WIDTH / 2) * nx;
			targetY -= (MARIO_BIG_BBOX_HEIGHT / 2 - MARIO_SMALL_BBOX_HEIGHT / 2);
		}

		float curX, curY;
		item->GetPosition(curX, curY);
		float kVx, kVy;
		kVx = (targetX - curX) / (float)fdt;
		kVy = (targetY - curY) / (float)fdt;
		item->SetSpeed(kVx, kVy);
		koopa->SetAccelation(0, 0);

		if (koopa->IsTimeOut())
		{
			isPickUp = false;
			DecreaseLevel();
		}
	}

}
void CMario::ReleaseItem(CGameObject* item) {
	if (item == nullptr || item->IsDeleted()) {
		return;
	}
	Koopa* koopa = dynamic_cast<Koopa*> (item);
	if (koopa == nullptr) return;

	startReleaseItem = GameClock::GetInstance()->GetTime();
	koopa->SetHolded(false);
	koopa->SetAccelation(0.f, KOOPA_GRAVITY);
	koopa->ReleaseByPlayer(this);
	//this->item = nullptr;
}

void CMario::UpdateTail(DWORD dt)
{
	if (tail == nullptr)
	{
		this->tail = new CMarioTail();
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		scene->AddObject(tail);
	}
	CMarioTail* tail = dynamic_cast<CMarioTail*>(this->tail);
	if (this->level != MARIO_LEVEL_TAIL)
	{
		tail->SetActive(false);
	}
	else
	{
		tail->SetActive(true);
	}

}

void CMario::SetAttack(bool value)
{
	if (tail == nullptr) return;
	CMarioTail* tail = dynamic_cast<CMarioTail*>(this->tail);
	float setX = this->x - nx * TAIL_BBOX_WIDTH / 2;
	float setY = this->y + TAIL_BBOX_HEIGHT;
	tail->SetPosition(setX, setY);
	tail->SetWhiping(value);
}
bool CMario::IsAttack()
{

	if (tail == nullptr) return false;
	CMarioTail* tail = dynamic_cast<CMarioTail*>(this->tail);
	return tail->IsWhiping();
}

bool CMario::IsReachToExpectedSpeed()
{
	if (this->GetLevel() == MARIO_LEVEL_TAIL)
		return abs(this->vx) >= MARIO_EXPECTED_SPEED;
	return false;
}

bool CMario::IsReadyToFly()
{
	bool b1 = IsReachToExpectedSpeed();
	bool b2 = (powerUnit >= MAX_POWER_UNIT);
	return b1 && b2;
}
bool CMario::IsMAXRunning()
{
	bool b1 = (abs(vx) >= MARIO_EXPECTED_SPEED) ? true : false;
	bool b2 = (powerUnit >= MAX_POWER_UNIT);
	return b1 && b2;
}

void CMario::SetFlying(bool value)
{
	isFlying = value;
	flyingTime = FLYING_TIME;
	if (startFlying == 0)
		startFlying = GameClock::GetInstance()->GetTime();
}

void CMario::SetSmallJump()
{
	if (!isOnPlatform)
		return;
	SetState(MARIO_STATE_JUMP);
	jumpedTime = MARIO_MAX_JUMP_TIME / 4;
}

void CMario::SetForEndGame(bool value)
{
	this->isEndGame = value;
	GameManager* gameManager = GameManager::GetInstance();
	gameManager->SetEndGame(this->isEndGame);
	if (this->isEndGame)
	{
		this->state = MARIO_STATE_ENDGAME;
		SetState(state);
	}
}

void CMario::SetForEntryPipeDown()
{
	if (!canEntryPipe) return;

	if (isPrepareEntry || isEntryPipe) return;

	//if (GetLevel() == MARIO_LEVEL_TAIL || GetLevel() == MARIO_LEVEL_BIG)
	//{
	//	y += 5;
	//}
	//else
	y += 5;
	isEntryDown = true;

	SetState(MARIO_STATE_PREPARE_ENTRY_PIPE);
	return;

}

void CMario::SetForEntryPipeUp()
{
	if (!canEntryPipe) return;

	if (isPrepareEntry || isEntryPipe) return;

	vy = -0.02f;
	DebugOut(L"Pre %f, %f \n", x, y);
	y -= 5;
	DebugOut(L"new %f, %f \n", x, y);
	isEntryDown = false;

	SetState(MARIO_STATE_ENTRY_PIPE);
	return;

}

void CMario::SetLinked(bool value1, bool value2, DropLift* dropLift)
{
	//isLinkedLeft = value1;
	//isLinkedUp = value2;
}

void CMario::SetIsStickToPlatform(DropLift* dropLift)
{
	this->movingPlatform = dropLift;
	if (movingPlatform) isLinked = true;
	else isLinked = false;
}

void CMario::DisableAllAction()
{
	isSitting = false;
	isPowerUp = false;
	isPickUp = false;
	isEntryPipe = false;
	isPrepareEntry = false;
	isExitPipe = false;
	SetAttack(false);
	isRecovering = false;
	isPowerUp = false;

	maxVx = 0.0f;
	vy = 0.0f;
	vx = 0.0f;
	ax = 0.0f;
	ay = 0.0f;
}