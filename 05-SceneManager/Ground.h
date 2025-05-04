#pragma once
#include "GameObject.h"
#define CELL_WIDTH 16
#define CELL_HEIGHT 16
class Ground : public CGameObject
{
private:
	int width; // cell units
	int height; // cell units
public:
	Ground(float x, float y, int width, int height) : CGameObject(x, y)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
	int IsColliable() { return 0; }
	int IsBlocking() { return 1; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void Render() override;
};

