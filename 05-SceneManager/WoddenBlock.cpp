#include "WoddenBlock.h"
#define CELL_SIZE 16
void WoddenBlock::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	//Render first column
	sprites->Get(gridBlockId[0][0])->Draw(x, y);
	sprites->Get(gridBlockId[1][0])->Draw(x, y + CELL_SIZE);
	//Render last column
	sprites->Get(gridBlockId[0][2])->Draw(x + (width - 1) * CELL_SIZE, y);
	sprites->Get(gridBlockId[1][2])->Draw(x + (width - 1) * CELL_SIZE, y + CELL_SIZE);
	//Render middle
	for (int i = 1; i < width - 1; i++)
	{
		sprites->Get(gridBlockId[0][1])->Draw(x + i * CELL_SIZE, y);
		sprites->Get(gridBlockId[1][1])->Draw(x + i * CELL_SIZE, y + CELL_SIZE);
	}
}

void WoddenBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CELL_SIZE / 2;
	t = y - CELL_SIZE / 2;
	r = l + width * CELL_SIZE;
	b = t + height * CELL_SIZE;
}
