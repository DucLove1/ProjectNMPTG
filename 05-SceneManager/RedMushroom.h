#pragma once
#include "Mushroom.h"
class RedMushroom : public CMushroom
{
	public:
	RedMushroom(float x, float y, int nx) : CMushroom(x, y, nx)
	{
	}
	void Render()
	{
		if(isActive)
		CAnimations::GetInstance()->Get(ID_ANI_MUSHROOM)->Render(x, y);
	}
	void Touched() override;
};

