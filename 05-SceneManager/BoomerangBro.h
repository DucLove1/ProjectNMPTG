#pragma once
#include "CEnemy.h"
#include <queue>
#include "Boomerang.h"
#include <random>
using namespace std;
class BoomerangBro : public CEnemy
{
	enum
	{
		STEP_FRONT = 0,
		STEP_BACK = 1,
		STOP = 2,
		THROW = 3,
		DIE_TOP = 4,
		DIE_BOTTOM = 5,
	};
	vector<pair<ULONGLONG, int>> phases = { {0, 0}, {800, 3},{850,0}, { 1200, 2 },
										{1250, 1}, {2050, 3}, {2100, 1} , { 2450, 2 },
										{ 2500, 0 }, {3700,2},{3750,1},{4950,2},{5000,-1} };
	int indexCurPhase;
	CGameObject* mario;
	int GetAnimationId();
	void SetStateBoomerangBro();
	int numberBoomerang;
	ULONGLONG timer;
	bool canThrow;
	random_device rd;
	mt19937 gen;
	uniform_int_distribution<int> dis;
public:
	BoomerangBro(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b) override;
	void Render() override;
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = nullptr) override;
	void OnNoCollision(DWORD dt) override;
	void OnCollisionWith(LPCOLLISIONEVENT e) override;
	void KickedFromTop(CGameObject*) override;
	void KnockedOut(CGameObject*) override {};
	void TouchTwoSide(CGameObject*) override {};
	void KickedFromBottom(CGameObject*) override ;
	int IsCollidable() override { return this->state != DIE_TOP && this->state !=DIE_BOTTOM; }
	int IsBlocking() override { return 0; };
	bool IsAlive() override { return state != DIE_TOP && state != DIE_BOTTOM; }
};

