#pragma once
#include "GameObject.h"
#define ID_TEX_TILE 30
#define DISTANCE_BETWEEN_BLOCKS 8.0f
#define CELL_WIDTH 8.0f
#define CELL_HEIGHT 8.0f
#define ID_SPRITE_SHADOW_CORNER 114001
#define ID_SPRITE_SHADOW_EDGE	115001
#define ID_SPRITE_SHADOW_CORNER_LEFT 114002
#define ID_SPRITE_SHADOW_CORNER_RIGHT 114003
class Block : public CGameObject
{
private:
	int unitHeight;			// Unit: cell
	int unitWidth;
	vector<vector<int>> gridBlockId;
	bool isShadowBottom;
	void GetGrid(int color)
	{
		//gridBlockId.resize(3, vector<int>(3, 0));
		switch (color)
		{
		case Color::BEIGE:
			gridBlockId = { { 110001, 110002, 110003 },
				{ 110004, 110005, 110006 },
				{ 110007, 110008, 110009 }
			};
			break;
		case Color::BLUE:
			gridBlockId = {
	{ 111001, 111002, 111003 },
	{ 111004, 111005, 111006 },
	{ 111007, 111008, 111009 }
			};
			break;
		case Color::GREEN:
			gridBlockId = {
	{ 112001, 112002, 112003 },
	{ 112004, 112005, 112006 },
	{ 112007, 112008, 112009 }
			};
			break;
		case Color::WHITE:
			gridBlockId = {
	{ 113001, 113002, 113003 },
	{ 113004, 113005, 113006 },
	{ 113007, 113008, 113009 }
			};
			break;
		default:
			break;
		}
	}
public:
	enum Color
	{
		BEIGE,
		BLUE,
		GREEN,
		WHITE
	};
	Block(float x, float y, int unitWidth, int unitHeight, int color, bool isShadowBottom = false)
		: CGameObject(x, y)
	{
		this->unitWidth = unitWidth;
		this->unitHeight = unitHeight;
		GetGrid(color);
		this->isShadowBottom = isShadowBottom;
	}
	void Render() override;
	void Update(DWORD dt) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b) override;
	int IsDirectionColliable(float nx, float ny) override
	{
		return (nx == 0 && ny == -1) ? 1 : 0;
	};
};


