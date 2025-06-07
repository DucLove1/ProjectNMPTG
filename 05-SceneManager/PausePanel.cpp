#include "PausePanel.h"
#include "Animations.h"
#include "Game.h"
#include "GameManager.h"


void CPausePanel::Render()
{
	if (!GameManager::GetInstance()->IsPausedGame()) return;
	this->id = 48001;
	SetPosition(136.0f, 100.0f);
	CUserInterface::Render();
}