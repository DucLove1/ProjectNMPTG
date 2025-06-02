#pragma once
#include "GameObject.h"
#include "debug.h"
#define BUTTON_STATE_PRESSED 0
#define BUTTON_STATE_NORMAL 1
#define BUTTON_STATE_NOT_PRESSED 2
class Button : public CGameObject
{
private: 
	bool isActive = false;
	public:
		Button(float x, float y) : CGameObject(x, y)
		{
			SetState(BUTTON_STATE_NOT_PRESSED);
		}
		void Render() override;
		void GetBoundingBox(float& l, float& t, float& r, float& b) override;
		void SetState(int state) override;
		void GetPress();
		int IsBlocking() override { return state == BUTTON_STATE_NORMAL; } // Button is not blocking
		bool IsPressed() { return this->state == BUTTON_STATE_PRESSED; }
		void IsAppear();
};

