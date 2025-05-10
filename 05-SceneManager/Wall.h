#pragma once
#include "GameObject.h"
class Wall : public CGameObject
{
	public:
	Wall(float x, float y) : CGameObject(x, y)
	{
	}
	void Render() { RenderBoundingBox(); };
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 0; }
	int IsBlocking() { return 1; }
};

