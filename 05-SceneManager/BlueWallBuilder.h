#pragma once
#include "GameObject.h"
class BlueWallBuilder : public CGameObject
{
private:
	int width;
	int height;
public:
	BlueWallBuilder(float x, float y, int width, int height) : CGameObject(x, y)
	{
		this->width = width;
		this->height = height;
	}
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsBlocking() override { return 1; } // this is a block
};

