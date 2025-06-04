#pragma once
#include "GameObject.h"

#define BORDER_POSITION_X 0
#define BORDER_POSITION_Y 192
#define BORDER_WIDTH 274
#define BORDER_HEIGHT 38

class CUserInterface :  public CGameObject

{
protected: 
	int id;
public:
	CUserInterface(float x, float y) : CGameObject(x, y)
	{
		this->x = x;
		this->y = y;
		id = 0;
	}
	void Render() override;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override
	{
		left = x - 10;
		top = y - 10;
		right = left + 20;
		bottom = top + 20;
	}

	int IsColliable() { return 0; }
};

