#pragma once
#include "GameObject.h"
class RectanglePlatform: public CGameObject
{
private:
	int width;
	int height;
	vector<vector<int>> gridBlockId;
public:
	RectanglePlatform(float x, float y, int width, int height, vector<vector<int>>& gridId)
		: CGameObject(x, y)
	{
		this->width = width;
		this->height = height;
		//get grid id
		for (int row = 0; row < gridId.size(); row++)
		{
			vector<int> rowGridId;
			for (int col = 0; col < gridId[row].size(); col++)
			{
				rowGridId.push_back(gridId[row][col]);
			}
			this->gridBlockId.push_back(rowGridId);
		}
	}
	void Render() override;
	void GetBoundingBox(float& l, float& t, float& r, float& b) override;
	int IsDirectionColliable(float nx, float ny) override
	{
		if (nx == 0 && ny == -1) return 1;
		return 0;
	}
};

