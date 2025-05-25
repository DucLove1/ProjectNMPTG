#pragma once
#include "CEnemy.h"
#include "PlayScene.h"
#define PIRANHA_PLANT_BBOX_WIDTH 16
#define PIRANHA_PLANT_BBOX_HEIGHT 24
#define TIME_WAIT_TO_HIDE 2000
#define TIME_WAIT_TO_APPEAR 2000
#define SPEED_Y 0.1f
#define DISTANCE_TO_APPEAR 28.0f
class PiranhaPlant: public CEnemy
{
private:
	ULONGLONG timer;
	float maxY, minY;
	CGameObject* mario;
	void UpdateStateAppear(DWORD dt);
	void UpdateStateHide(DWORD dt);
public:
	PiranhaPlant(float x, float y) : CEnemy(x, y)
	{
		this->timer = -1;
		this->ax = 0;
		this->ay = 0;
		this->minY = y - 27;
		this->maxY = y;
		this->state = HIDE;
		this->mario = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	}
	enum State
	{
		HIDE,
		APPEAR
	};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void KnockedOut(CGameObject*)override;
	void KickedFromBottom(CGameObject*) override;
};

