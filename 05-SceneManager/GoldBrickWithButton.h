#pragma once
#include "GoldBrick.h"
#include "BreakableGoldBrick.h"
#include "Button.h"
#include "PlayScene.h"
class GoldBrickWithButton: public GoldBrick
{
private:
	Button* button = nullptr;
public:
	GoldBrickWithButton(float x, float y, vector<BreakableGoldBrick*>& bricks) : GoldBrick(x, y)
	{
		button = new Button(x, y);
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(button);
		for(BreakableGoldBrick* brick : bricks)
		{
			brick->AddButton(button);
		}
	}
    void GotHit(LPCOLLISIONEVENT e) override;
};

