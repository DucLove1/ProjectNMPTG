#include "SpawnEnemy.h"
#include "PlayScene.h"
#include "GreenKoopa.h"
#include "Goomba.h"
#include "Game.h"
#include "debug.h"
#include "Mario.h"
void SpawnEnemy::GetEnemies(vector<pair<int, int>>& enemies)
{
	for (auto& type : enemies)
	{
		this->enemies.push(type);
	}
}
void SpawnEnemy::Spawn()
{
	if (this->enemies.empty())
	{
		return;
	}
	DebugOut(L"Chay\n");
	CGameObject* enemy = nullptr;
	int type = this->enemies.front().first;
	int state = this->enemies.front().second;
	this->enemies.pop();
	switch (type)
	{
	case OBJECT_TYPE_GREEN_KOOPAS:
		enemy = new GreenKoopa(this->positionSpawnX, this->positionSpawnY, state);
		break;
	case OBJECT_TYPE_BROWN_GOOMBA:
		enemy = new CGoomba(this->positionSpawnX, this->positionSpawnY, GOOMBA, state);
		break;
	case OBJECT_TYPE_RED_GOOMBA:
		enemy = new CGoomba(this->positionSpawnX, this->positionSpawnY, RED_GOOMBA, state);
		break;
	default:
		break;
	}
	if (enemy != nullptr)
	{
		dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene())->AddObject(enemy);
	}
}

void SpawnEnemy::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BBOX_WIDTH / 2;
	t = y - BBOX_HEIGHT / 2;
	r = l + BBOX_WIDTH;
	b = t + BBOX_HEIGHT;
}

void SpawnEnemy::Render()
{
	RenderBoundingBox();
}

void SpawnEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if(this->enemies.empty())
	{
		this->Delete();
		return;
	}
	if (isSpawned)
	{
		if (startTime == -1)
		{
			this->Spawn();
			startTime = GetTickCount64();
		}
		else
		{
			if (GetTickCount64() - startTime > TIME_WAIT_TO_SPAWN)
			{
				this->Spawn();
				startTime = GetTickCount64();
			}
		}
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void SpawnEnemy::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//DebugOut(L"Trung gi do\n");
	//CMario* mario = dynamic_cast<CMario*>(e->obj);
	//if(mario == nullptr)
	//	DebugOut(L"Bi null\n");
	//if (dynamic_cast<CMario*>(e->obj))
	//{
	//	DebugOut(L"Trung mario\n");
	//	this->isSpawned = true;
	//}
}
void SpawnEnemy::OnNoCollision(DWORD dt)
{
}
void SpawnEnemy::TouchedByMario()
{
	this->isSpawned = true;
}
