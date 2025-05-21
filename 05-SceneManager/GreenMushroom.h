#pragma once
#include "Mushroom.h"
class GreenMushroom: public CMushroom
{
	public:
	GreenMushroom(float x, float y, int nx) : CMushroom(x, y, nx)
	{
	}
	void Render() override;
};

