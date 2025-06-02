#pragma once
#include "GoldBrick.h"
#include "BreakableGoldBrick.h"
#include "Button.h"
#include "PlayScene.h"
class GoldBrickWithButton: public GoldBrick
{
private:
	Button* button = nullptr;
	float minY;
	float maxY;
public:
	GoldBrickWithButton(float x, float y, vector<BreakableGoldBrick*>& bricks) : GoldBrick(x, y)
	{
		button = new Button(x, y);
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(button);
		for(BreakableGoldBrick* brick : bricks)
		{
			brick->AddButton(button);
		}
		this->minY = y - GOLD_BRICK_BBOX_HEIGHT / 2;
		this->maxY = y;
	}
    void GotHit(LPCOLLISIONEVENT e) override;
	void GoUp(DWORD dt);
	void GoDown(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e) override;
	void OnNoCollision(DWORD dt) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	int IsCollidable() override { return state!=STATE_GO_UP && this->active; }
};

