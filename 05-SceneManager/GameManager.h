#pragma once
#include <iostream>
class GameManager
{
private:
	static GameManager* instance;
	int curLevel;
	int coins;
	float speed;
	int remainingTime;
	int score;
	int lives;
	bool isPausedToTransform;
	bool isPausedGame;
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
	bool IsPausedToTransform() { return isPausedToTransform; }
	void SetPausedToTransform(bool isPaused) { isPausedToTransform = isPaused; }
	bool IsPausedGame() { return isPausedGame; }
	void SetPausedGame(bool isPaused) { isPausedGame = isPaused; }
};

