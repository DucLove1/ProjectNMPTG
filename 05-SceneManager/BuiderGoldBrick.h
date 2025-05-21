#pragma once
#include "GoldBrick.h"
#include "GameObject.h"
#define BUILD_NOMRAL 0
#define BUILD_GOLD_COIN 1
#define TYPE_NON 0
#define TYPE_BREAKABLE_GOLD_BRICK 1
#define TYPE_ITEM_GOLD_BRICK 2
#define TYPE_BUTTON_GOLD_BRICK 3
#define TYPE_GREEN_MUSHROOM_GOLD_BRICK 4
#define TYPE_MULTI_GOLD_BRICK 5
class BuiderGoldBrick: public CGameObject
{
	int width;
	int height;
	public:
		BuiderGoldBrick(float x, float y, int type, vector<vector<int>>& grid) : CGameObject(x, y)
		{
			this->width = width;
			this->height = height;
			Build(type, grid);
			this->Delete();
		}
		void GetBoundingBox(float& l, float& t, float& r, float& b) override { l = t = r = b = 0; };
		int IsBlocking() override { return 0; } // BuiderGoldBrick is not blocking
		int IsCollidable() override { return 0; } // BuiderGoldBrick is not collidable
		void Render() override {};
		void Build(int type, vector<vector<int>>& grid);
		void BuildGoldCoin(vector<vector<int>>& grid);
		void BuildNormal(vector<vector<int>>& grid);
};

