#include "BigTree.h"
#include "Sprites.h"
#include "AssetIDs.h"
#define DISTANCE_OF_TWO_BLOCK 16
void BigTree::Render()
{
	switch (position)
	{
	case FIRST:
		RenderFirst();
		break;
	case MIDDLE:
		RenderMiddle();
		break;
	case LAST:
		RenderLast();
		break;
	}
}

void BigTree::RenderFirst()
{
	// get instance of sprite
	CSprites* spriteInstance = CSprites::GetInstance();
	// head
	spriteInstance->Get(ID_SPRITE_BIG_TREE_LEFT_UP)->Draw(x, y);
	spriteInstance->Get(ID_SPRITE_BIG_TREE_RIGHT_UP)->Draw(x + DISTANCE_OF_TWO_BLOCK, y);
	// body
	for (int i = 1; i < height; i++)
	{
		spriteInstance->Get(ID_SPRITE_BIG_TREE_LEFT_DOWN)->Draw(x, y + DISTANCE_OF_TWO_BLOCK * i);
		spriteInstance->Get(ID_SPRITE_BIG_TREE_MIDDLE)->Draw(x + DISTANCE_OF_TWO_BLOCK, y + DISTANCE_OF_TWO_BLOCK * i);
	}
}

void BigTree::RenderMiddle()
{
	CSprites* spriteInstance = CSprites::GetInstance();
	// head
	spriteInstance->Get(ID_SPRITE_BIG_TREE_LEFT_UP)->Draw(x, y);
	spriteInstance->Get(ID_SPRITE_BIG_TREE_RIGHT_UP)->Draw(x + DISTANCE_OF_TWO_BLOCK, y);
	// middle
	if (height < 2)
		return;
	int i = 1;
	if (height > 2)
	{
		spriteInstance->Get(ID_SPRITE_BIG_TREE_MIDDLE)->Draw(x, y + DISTANCE_OF_TWO_BLOCK);
		spriteInstance->Get(ID_SPRITE_BIG_TREE_RIGHT_DOWN)->Draw(x + DISTANCE_OF_TWO_BLOCK, y + DISTANCE_OF_TWO_BLOCK);
		i++;
	}
	for (; i < height; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			spriteInstance->Get(ID_SPRITE_BIG_TREE_MIDDLE)->Draw(x + j * DISTANCE_OF_TWO_BLOCK, y + i * DISTANCE_OF_TWO_BLOCK);
		}
	}
}

void BigTree::RenderLast()
{
	// get instance of sprite
	CSprites* spriteInstance = CSprites::GetInstance();
	// head
	spriteInstance->Get(ID_SPRITE_BIG_TREE_LEFT_UP)->Draw(x, y);
	spriteInstance->Get(ID_SPRITE_BIG_TREE_RIGHT_UP)->Draw(x + DISTANCE_OF_TWO_BLOCK, y);
	// body
	for (int i = 1; i < height; i++)
	{
		spriteInstance->Get(ID_SPRITE_BIG_TREE_MIDDLE)->Draw(x, y + DISTANCE_OF_TWO_BLOCK * i);
		spriteInstance->Get(ID_SPRITE_BIG_TREE_RIGHT_DOWN)->Draw(x + DISTANCE_OF_TWO_BLOCK, y + DISTANCE_OF_TWO_BLOCK * i);
	}
}
