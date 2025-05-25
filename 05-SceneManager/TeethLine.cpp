#include "TeethLine.h"
#include "AssetIDs.h"
#define DISTANCE_BETWEEN_TWO_BLOCKS 16
void TeethLine::Render()
{
	CSprites* s = CSprites::GetInstance();
	float xx = x;
	float yy = y;

	// Render the teeth line
	for(int row = 0; row < unitHeight; row++)
	{
		for(int col = 0; col < unitWidth; col++)
		{
			s->Get(ID_SPRITE_TEETH)->Draw(xx + col * DISTANCE_BETWEEN_TWO_BLOCKS, yy + row * DISTANCE_BETWEEN_TWO_BLOCKS);
		}
	}
}

void TeethLine::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - DISTANCE_BETWEEN_TWO_BLOCKS/ 2;
	t = y - DISTANCE_BETWEEN_TWO_BLOCKS/ 2;
	r = l + unitWidth * DISTANCE_BETWEEN_TWO_BLOCKS;
	b = t + unitHeight * DISTANCE_BETWEEN_TWO_BLOCKS;
}
