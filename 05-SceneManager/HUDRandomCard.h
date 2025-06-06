#pragma once
#include "UserInterface.h"
class HUDRandomCard : public CUserInterface
{
private:
	int pos;
public:
	HUDRandomCard(float x, float y, int pos) : CUserInterface(x, y)
	{
		this->x = x;
		this->y = y;
		this->pos = pos;
	}
	void Render() override;

};

