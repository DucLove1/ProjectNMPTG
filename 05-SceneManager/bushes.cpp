
#include "Bushes.h"
#include "AssetIDs.h"
#define DISTANCE_OF_TWO_BLOCK 16
void Bushes::Render()
{
	CSprites* spriteInstance = CSprites::GetInstance();
	for (int i = 0; i < width; i++)
	{
		spriteInstance->Get(ID_SPRITE_BUSH)->Draw(x + i * DISTANCE_OF_TWO_BLOCK, y);
	}
}
