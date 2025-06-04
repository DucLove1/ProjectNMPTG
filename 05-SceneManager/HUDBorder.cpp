#include "HUDBorder.h"
#include "Animations.h"
#include "Game.h"

void CHUDBorder::Render()
{
	this->id = ID_ANI_HUD_BORDER;
	SetPosition(136.0f, 211.0f);
	CUserInterface::Render();
}