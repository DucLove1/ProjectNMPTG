#include "BackGroundBuilder.h"
#define SIZEOFTILE 16
void BackGroundBuilder::Render()
{
	// Render the start sprite
	for (int i = 0; i < height; i++)
	{
		CSprites::GetInstance()->Get(IdSpriteStart)->Draw(x, y + i * SIZEOFTILE);
	}
	// Render the middle sprites
	for(int i= 1; i < width - 1; i++)
	{
		for (int j = 0; j < height; j++)
		{
			CSprites::GetInstance()->Get(IdSpriteMiddle)->Draw(x + i * SIZEOFTILE, y + j * SIZEOFTILE);
		}
	}
	// Render the end sprite
	for (int i = 0; i < height; i++)
	{
		CSprites::GetInstance()->Get(IdSpriteEnd)->Draw(x + (width - 1) * SIZEOFTILE, y + i * SIZEOFTILE);
	}
}
