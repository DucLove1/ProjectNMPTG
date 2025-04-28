#pragma once
#include "BackgroundObject.h"
class Cloud: public BackgroundObject
{
private:
	int width; // number of middle of cloud
public:
	Cloud(float x, float y, int width)
		: BackgroundObject(x, y)
	{
		this->width = width;
	}
	void Render() override;
};

