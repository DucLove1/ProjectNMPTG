#pragma once
#include "BackgroundObject.h"
class Icon : public BackgroundObject
{
private:
	int Id;
	public:
	Icon(float x, float y, int id) : BackgroundObject(x, y)
	{
		this->Id = id;
	}
	void Render() override
	{
		CSprites::GetInstance()->Get(Id)->Draw(x, y);
	}
};

