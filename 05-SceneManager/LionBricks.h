#pragma once
#include "GameObject.h"
class LionBricks : public CGameObject
{
private:
	int width;
	int height;
public:
	LionBricks(float x, float y, int width, int height)
		: CGameObject(x, y)
	{
		this->width = width;
		this->height = height;
	}
	void Render() override;
	void GetBoundingBox(float& l, float& t, float& r, float& b) override;

};

