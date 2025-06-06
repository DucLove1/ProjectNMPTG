#pragma once
#include <iostream>
#include "GameClock.h"
#include <vector>
#include "Game.h"
using namespace std;
//#include "Mario.h"
//try
#define LIMIT_GAME_TIME 300 //300 unit in mario ~~ 150 second
#define NONE -1
#define MUSHROOM_CARD_ID 0
#define FIRE_FLOWER_CARD_ID 1
#define STAR_CARD_ID 2
class GameManager
{
private:
	static GameManager* instance;
	int curLevel;
	int coins;
	int power;//0->7 maxpower. 0 is All off. x is x On
	ULONGLONG remainingTime;
	int score;
	int lives;
	bool isPausedToTransform;
	bool isPausedGame;
	bool isEndGame;
	int marioDirection;
	vector<int> cards={ -1, -1, -1 }; // this game has 3 cards
	int currentIndexWorld;

	GameManager() {
		curLevel = 1;
		coins = 0;
		power = 0.0f;
		remainingTime = LIMIT_GAME_TIME; // in unit of 700ms
		score = 0;
		lives = 3; // default lives
		isPausedToTransform = false;
		isPausedGame = false;
		marioDirection = 1; // default direction is right
		isEndGame = false;
		currentIndexWorld = CGame::GetInstance()->GetCurrentScene()->GetWordIndex(); // default world index is 0
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

	void SetPower(float power) { this->power = power; }
	float GetPower() { return power; }

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
	int GetCurrentIndexWorld() { return currentIndexWorld; }
	void Reset();
	void ResetTime();
	void AddCard(int cardID) 
	{ 
		for (int i = 0; i < cards.size(); i++)
		{
			if (cards[i] == -1)
			{
				cards[i] = cardID;
				return;
			}
		}
	}
	int GetCard(int index) 
	{ 
		if (index < 0 || index >= cards.size()) return NONE;
		return cards[index]; 
	}
};

