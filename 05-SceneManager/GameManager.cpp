#include "GameManager.h"
#include "GameClock.h"
#include "Game.h"
#include "Mario.h"
GameManager* GameManager::instance = NULL;
void GameManager::PauseToTransform()
{
	SetPausedToTransform(true);
	GameClock::GetInstance()->TempPause();
}

void GameManager::ResumeWhenDoneTransform()
{
	SetPausedToTransform(false);
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

void GameManager::Reset()
{
	curLevel = 1;
	coins = 0;
	remainingTime = LIMIT_GAME_TIME; // in unit of 700ms
	score = 0;
	lives = 3; // default lives
	isPausedToTransform = false;
	isPausedGame = false;
	marioDirection = 1; // default direction is right
	isEndGame = false;
	GameClock::GetInstance()->Reset();
	CGame::GetInstance()->GetCurrentScene()->GetWordIndex(); // default world index is 0
}

void GameManager::ResetTime()
{
	remainingTime = LIMIT_GAME_TIME; // in unit of 700ms
	GameClock::GetInstance()->Reset();
}
