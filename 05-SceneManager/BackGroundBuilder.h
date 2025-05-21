#pragma once
#include "BackgroundObject.h"
class BackGroundBuilder: public BackgroundObject
{
	int width;
	int height;
	int IdSpriteStart;
	int IdSpriteMiddle;
	int IdSpriteEnd;
public:
	BackGroundBuilder(float x, float y, int width, int height, int IdSpriteStart, int IdSpriteMiddle, int IdSpriteEnd)
		: BackgroundObject(x, y)
	{
		this->width = width;
		this->height = height;
		this->IdSpriteStart = IdSpriteStart;
		this->IdSpriteMiddle = IdSpriteMiddle;
		this->IdSpriteEnd = IdSpriteEnd;
	}
	void Render() override;

};

