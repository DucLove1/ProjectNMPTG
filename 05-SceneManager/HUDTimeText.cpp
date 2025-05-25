#include "HUDTimeText.h"
#include "GameManager.h"
#include "debug.h"

void CHUDTimeText::Render()
{
	//string time = to_string(GameManager::GetInstance()
	//	->GetRemainingTime());
	string time = to_string(GameManager::GetInstance()
		->CalculateRemainingTime());
	
	SetText(time);
	FillWithZeroes(time);
	CTextMeshPro::Render();
}

void CHUDTimeText::FillWithZeroes(string& time)
{
	int sz = time.length();
	if (sz > MAX_LENGTH)
		return;
	while (time.length() <= MAX_LENGTH)
	{
		time = "0" + time;
	}
}
