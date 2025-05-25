#pragma once
#include "CEnemy.h"
#include "Game.h"
#include "PlayScene.h"
#include "Pipe.h"
#include <vector>
#include "VenusBullet.h"
#define RED 0
#define GREEN 1
#define RED_BBOX_WIDTH 16
#define RED_BBOX_HEIGHT 32
#define GREEN_BBOX_WIDTH 16
#define GREEN_BBOX_HEIGHT 25
#define TIME_WAIT_TO_FIRE 1000
#define TIME_WAIT_TO_HIDE 2000
#define TIME_WAIT_TO_APPEAR 2000
#define TIME_WAIT_TO_ATTACK 3000
#define SPEED_Y 0.1f
#define DISTANCE_TO_APPEAR 28.0f
class Venus: public CEnemy
{
	private:
		CGameObject* mario;
		int ny;
		ULONGLONG timer;
		float maxY, minY;
		int cur_quarant;
		int type;
		VenusBullet* bullet;
		vector<vector<int>> angles = { {20,45},{135,160},{200,225},{315,340} };
		void FollowMario();
		void UpdateStateAppear(DWORD dt);
		void UpdateStateAttack(DWORD dt);
		void UpdateStateHide(DWORD dt);
		float ChooseAngle();
	public:
	Venus(float x, float y, int type) : CEnemy(x, y)
	{
		this->mario = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		this->ny = 1;
		this->timer = -1;
		this->ax = 0;
		this->ay = 0;
		this->type = type;
		this->minY = (this->type == RED) ? (y - 32) : (y-27);
		this->maxY = y + 16;
		this->state = HIDE;
		this->cur_quarant = 0;
		this->bullet = new VenusBullet(x, y);
		// add bullet into current play scene
		dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene())->AddObject(this->bullet);
	}
	enum State
	{
		APPEAR,
		HIDE,
		ATTACK
	};
	void Render();
	int FindQuardrant();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	void KickedFromTop(CGameObject* obj) { return; }
	void KickedFromBottom(CGameObject* obj);
	void KnockedOut(CGameObject* obj);
	void TouchTwoSide(CGameObject* obj) { return; }
	int IsColliable() { return this->y <= maxY - 10; }
};

