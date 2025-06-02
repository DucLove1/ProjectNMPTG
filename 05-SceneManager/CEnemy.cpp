#include "CEnemy.h"
#include "ComboScoreSystemMario.h"
#include "GameManager.h"
#include "Effect.h"
#include "PlayScene.h"
void CEnemy::KickedFromTop(CGameObject*)
{
	// get score and increase combo score
	ComboScoreSystemMario* comboScoreSystem = ComboScoreSystemMario::GetInstance();
	int score = comboScoreSystem->GetScore();
	comboScoreSystem->Increase();
	// add score to game manager
	if (score == UP1)
	{
		GameManager::GetInstance()->AddLives(1);
	}
	else
	GameManager::GetInstance()->AddScore(score);
	// add effect
	Effect* effect = new Effect(this->x, this->y - 16, score);
	((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(effect);
}
