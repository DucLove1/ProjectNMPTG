#include "Cloud.h"
#include "AssetIDs.h"
#define CLOUD_WIDTH 16 // width of middle of cloud
#define CLOUD_DISTANCE_OF_MIDDLE_AND_OTHER 8 // distance of middle cloud and begin or end cloud
void Cloud::Render()
{
	CSprites* s = CSprites::GetInstance();
	// Render begin of cloud
	s->Get(ID_SPRITE_CLOUD_BEGIN)->Draw(x, y);
	// Render middle of cloud
	// first cloud
	float xCloud = this->x + CLOUD_DISTANCE_OF_MIDDLE_AND_OTHER / 2 + CLOUD_WIDTH/2;
	for (int i = 0; i < width; i++)
	{
		s->Get(ID_SPRITE_CLOUD_MIDDLE)->Draw(xCloud, y);
		xCloud += CLOUD_WIDTH;
	}
	// Render end of cloud
	s->Get(ID_SPRITE_CLOUD_END)->Draw(xCloud - CLOUD_DISTANCE_OF_MIDDLE_AND_OTHER / 2, y);
}
