#include "HUDBorder.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "Game.h"

void CHUDBorder::Render()
{
	this->id = ID_ANI_HUD_BORDER;
	CUserInterface::Render();
}