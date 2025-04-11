#include "Block.h"
#include "debug.h"

void Block::Render()
{
	CSprites* s = CSprites::GetInstance();
	float xx = x;
	float yy = y;
	// 4 goc
	s->Get(gridBlockId[0][0])->Draw(xx, yy);
	s->Get(gridBlockId[0][2])->Draw(xx + (unitWidth - 1) * DISTANCE_BETWEEN_BLOCKS, yy);
	s->Get(gridBlockId[2][0])->Draw(xx, yy + (unitHeight - 1) * DISTANCE_BETWEEN_BLOCKS);
	s->Get(gridBlockId[2][2])->Draw(xx + (unitWidth - 1) * DISTANCE_BETWEEN_BLOCKS, yy + (unitHeight - 1) * DISTANCE_BETWEEN_BLOCKS);
	// canh tren row = 0
	for (int col = 1; col < unitWidth - 1; col++)
	{
		s->Get(gridBlockId[0][1])->Draw(xx + col * DISTANCE_BETWEEN_BLOCKS, yy);
	}
	// canh ben trai col = 0
	for (int row = 1; row < unitHeight - 1; row++)
	{
		s->Get(gridBlockId[1][0])->Draw(xx, yy + row * DISTANCE_BETWEEN_BLOCKS);
	}
	// canh ben phai col = unitWidth - 1
	for (int row = 1; row < unitHeight - 1; row++)
	{
		s->Get(gridBlockId[1][2])->Draw(xx + (unitWidth - 1) * DISTANCE_BETWEEN_BLOCKS, yy + row * DISTANCE_BETWEEN_BLOCKS);
	}
	// canh duoi row = unitHeight - 1
	for (int col = 1; col < unitWidth - 1; col++)
	{
		s->Get(gridBlockId[2][1])->Draw(xx + col * DISTANCE_BETWEEN_BLOCKS, yy + (unitHeight - 1) * DISTANCE_BETWEEN_BLOCKS);
	}
	// ben trong
	for (int row = 1; row < unitHeight - 1; row++)
	{
		for (int col = 1; col < unitWidth - 1; col++)
		{
			s->Get(gridBlockId[1][1])->Draw(xx + col * DISTANCE_BETWEEN_BLOCKS, yy + row * DISTANCE_BETWEEN_BLOCKS);
		}
	}
	// shadow
	s->Get(ID_SPRITE_SHADOW_CORNER)->Draw(xx + unitWidth * DISTANCE_BETWEEN_BLOCKS, yy + DISTANCE_BETWEEN_BLOCKS);
	for (int i = 2; i < unitHeight; i++)
	{
		s->Get(ID_SPRITE_SHADOW_EDGE)->Draw(xx + unitWidth * DISTANCE_BETWEEN_BLOCKS, yy + i * DISTANCE_BETWEEN_BLOCKS);
	}
}

void Block::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CELL_WIDTH / 2;
	t = y - CELL_HEIGHT / 2;
	r = l + unitWidth * CELL_WIDTH;
	b = t + unitHeight * CELL_HEIGHT;
}

