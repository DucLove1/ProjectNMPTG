#pragma once
#include "GameObject.h"
#include "BreakableGoldBrick.h"
#include "debug.h"
#define BUTTON_STATE_PRESSED 0
#define BUTTON_STATE_NORMAL 1
class Button : public CGameObject
{
private:
	vector<BreakableGoldBrick*> bricks; // Pointer to the vector of breakable gold bricks
	public:
		Button(float x, float y, vector<BreakableGoldBrick*>& bricks) : CGameObject(x, y)
		{
			SetState(BUTTON_STATE_NORMAL);
			for(BreakableGoldBrick* brick : bricks)
			{
				this->bricks.emplace_back(brick);
			}
			DebugOut(L"size %d", bricks.size());
		}
		void Render() override;
		void GetBoundingBox(float& l, float& t, float& r, float& b) override;
		void SetState(int state) override;
		void GetPress();
		int IsBlocking() override { return 0; } // Button is not blocking
};

