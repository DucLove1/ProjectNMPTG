#include "BoomerangBro.h"
#include "PlayScene.h"
#include "AssetIDs.h"
#include "Animations.h"
#include "Boomerang.h"
#include "GameClock.h"
#define BOOMERANG_BRO_WIDTH 16
#define BOOMERANG_BRO_HEIGHT 22
#define VX 0.05f
#define VY 0.1f
#define TIMES_ANIM_WALK 100
#define TIME_STEP_FRONT 0
#define TIME_THROW_1 800
#define TIME_STEP_FRONTT 850
#define TIME_STOP_1 1200
#define TIME_STEP_BACK 1250
#define TIME_THROW_2	2050
#define TIME_STEP_BACKK 2100
#define TIME_STOP_2 2450
#define TIME_STEP_FRONT_2 2500
#define TIME_STOP_3 3700
#define TIME_STEP_BACK_2 3750
#define TIME_STOP_4  4950
#define CYCLE_TIME 5000
#define TIME_JUMP 4000
BoomerangBro::BoomerangBro(float x, float y)
	: CEnemy(x, y)
{
	mario = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	nx = 1;
	SetSpeed(VX, VY);
	timesDoneAnimWalk = 0;
	numberBoomerang = 2;
	timer = GameClock::GetInstance()->GetTime();
	SetState(STEP_FRONT);
	indexCurPhase = 0;
	canThrow = false;
}
void BoomerangBro::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BOOMERANG_BRO_WIDTH / 2;
	t = y - BOOMERANG_BRO_HEIGHT / 2;
	r = l + BOOMERANG_BRO_WIDTH;
	b = t + BOOMERANG_BRO_HEIGHT;
}

void BoomerangBro::Render()
{
	int ani = GetAnimationId();
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	if (CAnimations::GetInstance()->Get(ani)->Done())
		timesDoneAnimWalk++;
}
void BoomerangBro::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	vy += 0.01 * dt;
	SetStateBoomerangBro();
	switch (state)
	{
	case STEP_FRONT:
		vx = abs(VX) * nx;
		break;
	case STEP_BACK:
		vx = -abs(VX) * nx;
		break;
	case THROW:
	{
		if (canThrow)
		{
			Boomerang* boomerang = new Boomerang(x-5, y-5);
			dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene())->AddObject(boomerang);
			boomerang->Throw();
			canThrow = false;
		}
		break;
	}
	case STOP:
		vx = 0;
		break;
	case DIE_TOP:
		break;
	case DIE_BOTTOM:
		break;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
	DebugOut(L"vx = %f", vx);
}
void BoomerangBro::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void BoomerangBro::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<Boomerang*>(e->obj))
	{
		Boomerang* boomerang = dynamic_cast<Boomerang*>(e->obj);
		e->obj->Delete();
	}
	if (!e->obj->IsBlocking())
	{
		return;
	}
	if (e->ny != 0)
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
int BoomerangBro::GetAnimationId()
{
	int id = ID_ANI_BOOMERANG_BRO_WALKING_RIGHT;
	switch (state)
	{
	case STEP_FRONT:
	case STEP_BACK:
		id = (nx == 1) ? ID_ANI_BOOMERANG_BRO_WALKING_RIGHT : ID_ANI_BOOMERANG_BRO_WALKING_LEFT;
		break;
	case STOP:
		id = (nx == 1) ? ID_ANI_BOOMERANG_BRO_STOP_RIGHT : ID_ANI_BOOMERANG_BRO_STOP_LEFT;
		break;
	case THROW:
		id = (nx == 1) ? ID_ANI_BOOMERANG_BRO_THROW_RIGHT : ID_ANI_BOOMERANG_BRO_THROW_LEFT;
		break;
	case DIE_TOP:
		id = ID_ANI_BOOMERANG_BRO_DIE_FROM_TOP;
		break;
	case DIE_BOTTOM:
		id = ID_ANI_BOOMERANG_BRO_DIE_FROM_BOTTOM;
		break;
	}
	return id;
}

void BoomerangBro::SetStateBoomerangBro()
{
	ULONGLONG cur = GameClock::GetInstance()->GetTime();
	ULONGLONG time = cur - timer;
	if (indexCurPhase == phases.size() - 1)
	{
		indexCurPhase = 0;
		timer = cur;
		SetState(phases[indexCurPhase].second);
		return;
	}
	if (time >= phases[indexCurPhase + 1].first)
	{
		indexCurPhase++;
		SetState(phases[indexCurPhase].second);
		if (indexCurPhase == 1 || indexCurPhase == 5)
			canThrow = true;
	}
}
