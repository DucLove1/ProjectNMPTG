#pragma once
#include "GoldBrick.h"
#include "BreakableGoldBrick.h"
class GoldBrickWithButton: public GoldBrick
{
private:
	vector<BreakableGoldBrick*> bricks;
public:
	GoldBrickWithButton(float x, float y, vector<BreakableGoldBrick*>& bricks) : GoldBrick(x, y)
	{
		for(BreakableGoldBrick* brick : bricks)
		{
			this->bricks.emplace_back(brick);
		}
	}
    void GotHit(LPCOLLISIONEVENT e) override;
};

