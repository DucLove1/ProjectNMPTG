#include "HUDScoreText.h"
#include "GameManager.h"
#include "debug.h"

void CHUDScoreText::Render()
{
	string score = std::to_string(GameManager::GetInstance()
		->GetScore());
	FillWithZeroes(score);
	SetText(score);
	CTextMeshPro::Render();
}

void CHUDScoreText::FillWithZeroes(string &score)
{
	int sz = score.length();
	if (sz > MAX_LENGTH)
		return;
	while (score.length() <= MAX_LENGTH)
	{
		score = "0" + score;
	}
}
