#pragma once
#include <windows.h>
#include <iostream>
class GameClock
{
private:
    static GameClock* instance;
    ULONGLONG startTime;
    ULONGLONG pauseTime;
    ULONGLONG accumulatedPause;
    bool isPaused;
    GameClock() {
        startTime = GetTickCount64();
        pauseTime = 0;
        accumulatedPause = 0;
        isPaused = false;
    }
public:
    static GameClock* GetInstance() {
		if (instance == NULL) {
			instance = new GameClock();
		}
		return instance;
	}
    void Pause() {
        if (!isPaused) {
            pauseTime = GetTickCount64();
            isPaused = true;
        }
    }

    void Resume() {
        if (isPaused) {
            accumulatedPause += GetTickCount64() - pauseTime;
            isPaused = false;
        }
    }

    ULONGLONG GetTime() const {
        if (isPaused) {
            return pauseTime - startTime - accumulatedPause;
        }
        return GetTickCount64() - startTime - accumulatedPause;
    }

    bool IsPaused() const {
        return isPaused;
    }
};

