#include "HUDLifeText.h"
#include "GameManager.h"

void CHUDLifeText::Render()
{
	string lifePoint = to_string(GameManager::GetInstance()
		->GetLives());
	//lifePoint = "3";

	SetText(lifePoint);

	CTextMeshPro::Render();
}