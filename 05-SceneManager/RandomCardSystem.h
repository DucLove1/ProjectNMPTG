#pragma once
#include "GameObject.h"
class RandomCardSystem : public CGameObject
{
public:
	RandomCardSystem(float x, float y);

	void GetBoundingBox(float& l, float& t, float& r, float& b) override
	{
		l = t = r = b = 0;
	}

	void Render() override;

	int IsCollidable() override { return 0; }
	int IsBlocking() override { return 0; }
};

