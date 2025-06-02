#pragma once
#include "GameObject.h"
#include "CEnemy.h"
#include "RedKoopa.h"
#define SENSOR_BBOX_WIDTH 1
#define SENSOR_BBOX_HEIGHT 26
#define ENEMY_BBOX_WIDTH 18
class Sensor : public CGameObject
{
private:
	CEnemy* enemy = NULL;
	float ay;
	bool isOn;
public:
	Sensor(CEnemy* enemy)
		: CGameObject()
	{
		this->enemy = enemy;
		enemy->GetPosition(this->x, this->y);
		//this->x -= (ENEMY_BBOX_WIDTH + 5);
		ay = 0.001f;
		vy = 0;
		isOn = false;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render() { RenderBoundingBox();  }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void FollowEnemy();
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void TurnOn() { isOn = true; }
	void TurnOff() { isOn = false; }
};


