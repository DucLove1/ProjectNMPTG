#include "LionBricks.h"
#include "AssetIDs.h"
#define LIONBRICKS_BBOX_WIDTH 16
void LionBricks::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	for(int row = 0; row < height; row++)
	{
		for(int col = 0; col < width; col++)
		{
			sprites->Get(ID_SPRITE_LION_BRICK)->Draw(x + col * LIONBRICKS_BBOX_WIDTH, y + row * LIONBRICKS_BBOX_WIDTH);
		}
	}
}

void LionBricks::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LIONBRICKS_BBOX_WIDTH / 2;
	t = y - LIONBRICKS_BBOX_WIDTH / 2;
	r = l + LIONBRICKS_BBOX_WIDTH * width;
	b = t + LIONBRICKS_BBOX_WIDTH * height;
}
