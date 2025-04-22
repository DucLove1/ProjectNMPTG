#include "Ground.h"
#include "AssetIDs.h"
void Ground::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - CELL_WIDTH / 2;
	top = y - CELL_HEIGHT / 2;
	right = left + CELL_WIDTH * width;
	bottom = top + CELL_HEIGHT * height;
}

void Ground::Render()
{
	CSprites* s = CSprites::GetInstance();
	//up begin
	s->Get(ID_SPRITE_GROUND_UP_BEGIN)->Draw(x, y);
	//up middle
	for (int i = 1; i < width - 1; i++)
	{
		s->Get(ID_SPRITE_GROUND_UP_MIDDLE)->Draw(x + i * CELL_WIDTH, y);
	}
	//up end
	s->Get(ID_SPRITE_GROUND_UP_END)->Draw(x + (width - 1) * CELL_WIDTH, y);
	//down begin
	for(int i = 1; i < height; i++)
	{
		s->Get(ID_SPRITE_GROUND_DOWN_BEGIN)->Draw(x, y + i * CELL_HEIGHT);
	}
	//down middle
	for(int row = 1; row < height; row++)
	{
		for(int col = 1; col < width - 1; col++)
		{
			s->Get(ID_SPRITE_GROUND_DOWN_MIDDLE)->Draw(x + col * CELL_WIDTH, y + row * CELL_HEIGHT);
		}
	}
	//down end
	for(int i = 1; i < height; i++)
	{
		s->Get(ID_SPRITE_GROUND_DOWN_END)->Draw(x + (width - 1) * CELL_WIDTH, y + i * CELL_HEIGHT);
	}
}

