#pragma once
#include "CEnemy.h"
#include "Game.h"
#include "PlayScene.h"
#define RED 0
#define GREEN 1
#define BBOX_WIDTH 16
#define BBOX_HEIGHT 32
#define TIME_WAIT 3000
#define TIME_ATTACK 3000
#define TIME_
class Venus: public CEnemy
{
	private:
		CGameObject* mario;
		int ny;
		ULONGLONG timer;
		void FollowMario();
	public:
	Venus(float x, float y, int type) : CEnemy(x, y)
	{
		this->mario = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	}
	enum State
	{
		WAITING,
	    ATTACKING,
		KNOCKED_OUT,
	};
	void Render();
	void RenderRedVenus(int&);
	int FindQuardrant();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	// declare pure vitual functions 
	void KickedFromTop(CGameObject* obj) { return; }
	void KnockedOut(CGameObject* obj) { return; }
	void TouchTwoSide(CGameObject* obj) { return; }
	bool IsAlive() { return true; }


};

