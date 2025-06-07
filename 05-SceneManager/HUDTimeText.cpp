#include "HUDTimeText.h"
#include "GameManager.h"
#include "debug.h"
#include "Mario.h"
#include "Game.h"

void CHUDTimeText::Render()
{
	//string time = to_string(GameManager::GetInstance()
	//	->GetRemainingTime());
	ULONGLONG time =
		GameManager::GetInstance()->CalculateRemainingTime();
	if (time > 301)
	{
		time = 0;
	}
	else if (time <= 0)
		time = 0;
	string s_time = to_string(time);

	SetText(s_time);
	FillWithZeroes(s_time);
	CTextMeshPro::Render();

	if (time == 0)
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		mario->SetState(MARIO_STATE_DIE);
	}
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
