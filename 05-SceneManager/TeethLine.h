#pragma once
#include "GameObject.h"
class TeethLine: public CGameObject
{
	private:
	int unitHeight;			// Unit: cell
	int unitWidth;
public:
	TeethLine(float x, float y, int unitWidth, int unitHeight) : CGameObject(x, y)
	{
		this->unitWidth = unitWidth;
		this->unitHeight = unitHeight;
	}
	int IsBlocking() override { return 1; }
	int IsCollidable() override { return 0; } 
	int IsDirectionColliable(float nx, float ny) { return (nx == 0 && ny == -1) ? 1 : 0; }
	void Render() override;
	void GetBoundingBox(float& l, float& t, float& r, float& b) override;
};

