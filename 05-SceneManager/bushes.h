#pragma once
#include "BackgroundObject.h"
class Bushes : public BackgroundObject
{
private:
	int width;
public:
	Bushes(float x, float y, float width)
		: BackgroundObject(x, y)
	{
		this->width = width;
	}
	void Render() override;
};
