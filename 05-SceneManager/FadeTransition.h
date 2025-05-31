#pragma once
#include "GameObject.h"
#define VFADE_TRANSITION 0.001f
#define WIDTH 800
#define HEIGHT 600
class FadeTransition: public CGameObject
{
	float alpha;	// Alpha value for fade transition
	float duration; // Duration of the fade effect in milliseconds
	bool isFadingIn; // True if fading in, false if fading out
	DWORD startTime; // Start time of the fade effect
	public:
		FadeTransition(float x, float y, float duration, bool fadeIn = false)
		: CGameObject(x,y),duration(duration), isFadingIn(fadeIn), startTime(GetTickCount()) {
			alpha = fadeIn ? 0.0f : 1.0f; // Start with 0 for fade in, 1 for fade out
		}
		void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = nullptr) override;
		void Render() override;
		void GetBoundingBox(float& l, float& t, float& r, float& b) override;
		void RenderBoundingBox();
		int IsBlocking() override { return 0; } // Not blocking any movement
		int IsCollidable() override { return 0; } // Not collidable
};

