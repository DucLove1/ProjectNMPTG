#include "HUDLevel.h"
#include "GameManager.h"
#include "debug.h"

void CHUDLevel::Render()
{
	//string time = to_string(GameManager::GetInstance()
	//	->GetRemainingTime());
	string level = to_string(GameManager::GetInstance()->GetCurrentIndexWorld());

	SetText(level);
	CTextMeshPro::Render();
}

