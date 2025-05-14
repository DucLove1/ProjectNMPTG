#include "BuiderGoldBrick.h"
#include "BreakableGoldBrick.h"
#include "PlayScene.h"
#include "GoldBrickWithButton.h"
#include "ItemGoldBrick.h"
#define BLOCK_SIZE 16
void BuiderGoldBrick::Build(int type, vector<vector<int>>& grid)
{
	if (type == BUILD_GOLD_COIN)
	{
		BuildGoldCoin(grid);
	}
	else
	{
		BuildNormal(grid);
	}
}

void BuiderGoldBrick::BuildGoldCoin(vector<vector<int>>& grid)
{
	vector<BreakableGoldBrick*> goldBricks;
	float buttonX = 0, buttonY = 0;
	int width = grid.size();
	int height = grid[0].size();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float posX = this->x + i * BLOCK_SIZE;
			float posY = this->y + j * BLOCK_SIZE;
			switch (grid[j][i])
			{
			case TYPE_BREAKABLE_GOLD_BRICK:
			{
				BreakableGoldBrick* curBrick = new BreakableGoldBrick(posX, posY);
				goldBricks.emplace_back(curBrick);
				((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(curBrick);
				break;
			}
			case TYPE_BUTTON_GOLD_BRICK:
			{
				buttonX = posX;
				buttonY = posY;
				break;
			}
			}
		}
	}
	GoldBrickWithButton* brick = new GoldBrickWithButton(buttonX, buttonY, goldBricks);
	((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(brick);
}

void BuiderGoldBrick::BuildNormal(vector<vector<int>>& grid)
{
	int width = grid.size();
	int height = grid[0].size();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float posX = this->x + i * BLOCK_SIZE;
			float posY = this->y + j * BLOCK_SIZE;
			switch (grid[j][i])
			{
			case TYPE_BREAKABLE_GOLD_BRICK:
			{
				BreakableGoldBrick* curBrick = new BreakableGoldBrick(posX, posY);
				((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(curBrick);
				break;
			}
			case TYPE_ITEM_GOLD_BRICK:
				ItemGoldBrick* itemBrick = new ItemGoldBrick(posX, posY);
				((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(itemBrick);
				break;
			}
		}
	}
}

