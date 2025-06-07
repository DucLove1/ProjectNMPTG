#pragma once
#include "UserInterface.h"

class CPausePanel : 
	public CUserInterface
{
public:
	CPausePanel(float x, float y)
		: CUserInterface(x, y)
	{
		this->id = 48001;
	}

	void Render() override;
};

