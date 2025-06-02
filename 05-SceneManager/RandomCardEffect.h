#pragma once
#include "GameObject.h"
#include "GameClock.h"
#define MUSHROOM_CARD_ID 0
#define FIRE_FLOWER_CARD_ID 1
#define STAR_CARD_ID 2
class RandomCardEffect : public CGameObject
{
	private:
	int cardID; // 0, 1, 2
	ULONGLONG timer;
	public:
	RandomCardEffect(float x, float y, int cardID) : CGameObject(x, y)
	{
		this->cardID = cardID;
		this->timer = GameClock::GetInstance()->GetTime();
		vy = -0.1f;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) override;
	void Render() override;
	int IsCollidable() override { return 0; }
	int IsBlocking() override { return 0; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
};

