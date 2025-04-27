#pragma once
#include "BackgroundObject.h"
class BigTree: public BackgroundObject
{
public:
	enum POSITION 
	{
		FIRST, MIDDLE, LAST
	};
	BigTree(float x, float y, int height, int position = 0)
		: BackgroundObject(x, y)
	{
		this->position = position;
		this->height = height;
	}
private:
	int position; // first, middle or last
	int height; // height of the tree (unit)
	void Render() override;
	void RenderFirst();
	void RenderMiddle();
	void RenderLast();
};

