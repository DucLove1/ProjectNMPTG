#pragma once
#include <iostream>
#include "GameClock.h"
#include <vector>
using namespace std;
//#include "Mario.h"
//try
#define LIMIT_GAME_TIME 300 //300 unit in mario ~~ 150 second

class GameManager
{
private:
	static GameManager* instance;
	int curLevel;
	int coins;
	float speed;
	ULONGLONG remainingTime;
	int score;
	int lives;
	bool isPausedToTransform;
	bool isPausedGame;
	bool isEndGame;
	int marioDirection;
	vector<int> cards={ 0, 0, 0 }; // this game has 3 cards

	GameManager() {
		curLevel = 1;
		coins = 0;
		speed = 0.0f;
		remainingTime = LIMIT_GAME_TIME; // in unit of 700ms
		score = 0;
		lives = 3; // default lives
		isPausedToTransform = false;
		isPausedGame = false;
		marioDirection = 1; // default direction is right
		isEndGame = false;
	};
public:
	static GameManager* GetInstance()
	{
		if (instance == NULL) instance = new GameManager();
		return instance;
	}

	void SetCurLevel(int level) { curLevel = level; }
	int GetCurLevel() { return curLevel; }

	int GetCoins() { return coins; }
	void PlusCoins(int coins) { this->coins += coins; }

	void SetSpeed(float speed) { this->speed = speed; }
	float GetSpeed() { return speed; }

	int GetRemainingTime() { return remainingTime; }
	void MinusRemainingTime() { this->remainingTime--; }

	void PauseToTransform();
	void ResumeWhenDoneTransform();
	void PauseGame();
	void ResumeGame();

	void AddScore(int score) { this->score += score; }
	int GetScore() { return score; }

	void AddLives(int lives) { this->lives += lives; }
	int GetLives() { return lives; }

	bool IsPausedToTransform() { return isPausedToTransform; }
	void SetPausedToTransform(bool isPaused) { isPausedToTransform = isPaused; }
	bool IsPausedGame() { return isPausedGame; }
	void SetPausedGame(bool isPaused) { isPausedGame = isPaused; }

	void SetEndGame(bool isEnd) { isEndGame = isEnd; }
	bool IsEndGame() { return isEndGame; }

	ULONGLONG CalculateRemainingTime()
	{
		GameClock* clock = GameClock::GetInstance();
		ULONGLONG current = clock->GetTime();

		return LIMIT_GAME_TIME - (current / 700);
	}

	void SaveMarioState();
	void SetMarioDirection(int direction) { marioDirection = direction; }
	int GetMarioDirection() { return marioDirection; }
};

