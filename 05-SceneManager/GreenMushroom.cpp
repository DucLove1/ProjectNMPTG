#include "GreenMushroom.h"
#define ID_GREEN_MUSHROOM 220001
void GreenMushroom::Render()
{
	if(isActive)
	CSprites::GetInstance()->Get(ID_GREEN_MUSHROOM)->Draw(x, y);
}
