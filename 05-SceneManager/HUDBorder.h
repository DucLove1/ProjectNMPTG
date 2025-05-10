#pragma once
#include "UserInterface.h"
class CHUDBorder : public CUserInterface
{
public:
	CHUDBorder(float x, float y) : CUserInterface(x, y)
	{
		this->x = x;
		this->y = y;
	}
	void Render() override;
};

