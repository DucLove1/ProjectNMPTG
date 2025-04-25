#pragma once
#include "GameObject.h"
#include "CEnemy.h"
#include <queue>
#define TIME_WAIT_TO_SPAWN 1000
#define BBOX_WIDTH 16
#define BBOX_HEIGHT 100
class SpawnEnemy : public CGameObject
{
private:
	float positionSpawnX;
	float positionSpawnY;
	queue<pair<int,int>> enemies;
	bool isSpawned;
	ULONGLONG startTime;
public:
	SpawnEnemy(float x, float y, float positionSpawnX, float positionSpawnY, vector<pair<int,int>>& typeEnemy) : CGameObject(x, y)
	{
		this->x = x;
		this->y = y;
		this->positionSpawnX = positionSpawnX;
		this->positionSpawnY = positionSpawnY;
		this->isSpawned = false;
		this->startTime = -1;
		GetEnemies(typeEnemy);
	}
	void GetEnemies(vector<pair<int,int>>& enemies);
	void Spawn();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
	void OnCollisionWith(LPCOLLISIONEVENT e) override;
	void OnNoCollision(DWORD dt) override;

	void TouchedByMario();
	
};

