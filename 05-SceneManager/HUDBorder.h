#pragma once
#include "UserInterface.h"
#include "AssetIDs.h"

class CHUDBorder : public CUserInterface
{
public:
	CHUDBorder(float x, float y) : CUserInterface(x, y)
	{
		this->id = ID_ANI_HUD_BORDER;
	}
	void Render() override;
};

