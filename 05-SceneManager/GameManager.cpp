#include "GameManager.h"
#include "GameClock.h"
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
}

void GameManager::ResumeGame()
{
	GameClock::GetInstance()->Resume();
}
