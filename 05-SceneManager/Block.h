#pragma once
#include "GameObject.h"
#define ID_TEX_TILE 30
#define DISTANCE_BETWEEN_BLOCKS 8.0f
#define CELL_WIDTH 8.0f
#define CELL_HEIGHT 8.0f
#define ID_SPRITE_SHADOW_CORNER 114001
#define ID_SPRITE_SHADOW_EDGE	115001
class Block : public CGameObject
{
private:
	int unitHeight;			// Unit: cell
	int unitWidth;
	vector<vector<int>> gridBlockId;
public:
	Block(float x, float y, int unitWidth, int unitHeight, vector<vector<int>>& gridId)
		: CGameObject(x, y)
	{
		this->unitWidth = unitWidth;
		this->unitHeight = unitHeight;
		gridBlockId.resize(3);
		for (int row = 0; row < gridId.size(); row++)
		{
			for (int col = 0; col < gridId[0].size(); col++)
			{
				(this->gridBlockId[row]).push_back(gridId[row][col]);
			}
		}
	}
	void Render() override;
	void Update(DWORD dt) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b) override;
	int IsDirectionColliable(float nx, float ny) override
	{
		return (nx == 0 && ny == -1) ? 1 : 0;
	};
};


