#include "BlueWallBuilder.h"
#include "Sprites.h"
#include "AssetIDs.h"
#define BLUE_WALL_EDGE 16
void BlueWallBuilder::Render()
{
	for(int row = 0; row < height; row++)
	{
		for(int col = 0; col < width; col++)
		{
			CSprites::GetInstance()->Get(ID_SPRITE_BLUE_BRICK)->Draw(x + col * BLUE_WALL_EDGE, y + row * BLUE_WALL_EDGE);
		}
	}
}

void BlueWallBuilder::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BLUE_WALL_EDGE / 2;
	top = y - BLUE_WALL_EDGE / 2;
	right = left + width * BLUE_WALL_EDGE;
	bottom = top + height * BLUE_WALL_EDGE;
}
