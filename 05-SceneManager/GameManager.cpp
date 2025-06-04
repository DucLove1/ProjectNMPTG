#include "GameManager.h"
#include "GameClock.h"
#include "Game.h"
#include "Mario.h"
GameManager* GameManager::instance = NULL;
void GameManager::PauseToTransform()
{
	GameClock::GetInstance()->TempPause();
}

void GameManager::ResumeWhenDoneTransform()
{
	GameClock::GetInstance()->ResumeTempPause();
}

void GameManager::PauseGame()
{
	GameClock::GetInstance()->Pause();
	isPausedGame = true;
}

void GameManager::ResumeGame()
{
	GameClock::GetInstance()->Resume();
	isPausedGame = false;
}

void GameManager::SaveMarioState()
{
	//CMario* player = dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->GetPlayer());
	//if (player != nullptr)
	//{
	//	this->curLevel = player->GetLevel();
	//}
}
