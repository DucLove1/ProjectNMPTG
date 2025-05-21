#include "RectanglePlatform.h"
#define SIZEOFTILE 16
void RectanglePlatform::Render()
{
	// render left top corner
	CSprites::GetInstance()->Get(gridBlockId[0][0])->Draw(x, y);
	// render right top corner
	CSprites::GetInstance()->Get(gridBlockId[0][2])->Draw(x + (width - 1) * SIZEOFTILE, y);
	// render first column
	for (int i = 1; i < height; i++)
	{
		CSprites::GetInstance()->Get(gridBlockId[1][0])->Draw(x, y + i * SIZEOFTILE);
	}
	// render last column
	for (int i = 1; i < height; i++)
	{
		CSprites::GetInstance()->Get(gridBlockId[1][2])->Draw(x + (width - 1) * SIZEOFTILE, y + i * SIZEOFTILE);
	}
	// render first row
	for (int i = 1; i < width - 1; i++)
	{
		CSprites::GetInstance()->Get(gridBlockId[0][1])->Draw(x + i * SIZEOFTILE, y);
	}
	// render middle
	for (int i = 1; i < width - 1; i++)
	{
		for (int j = 1; j < height; j++)
		{
			CSprites::GetInstance()->Get(gridBlockId[1][1])->Draw(x + i * SIZEOFTILE, y + j * SIZEOFTILE);
		}
	}

}

void RectanglePlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SIZEOFTILE / 2;
	t = y - SIZEOFTILE / 2;
	r = l + width * SIZEOFTILE;
	b = t + height * SIZEOFTILE;
}
