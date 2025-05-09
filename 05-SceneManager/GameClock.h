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
    bool tempPaused;
    GameClock() {
        startTime = GetTickCount64();
        pauseTime = 0;
        accumulatedPause = 0;
        isPaused = false;
        tempPaused = false;
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
        if (isPaused || tempPaused) {
            return pauseTime - startTime - accumulatedPause;
        }
        return GetTickCount64() - startTime - accumulatedPause;
    }

    bool IsPaused() const {
        return isPaused;
    }

    bool IsTempPaused() const {
		return tempPaused;
	}

    void TempPause() {
        if (!tempPaused) {
            pauseTime = GetTickCount64();
			tempPaused = true;
		}
	}

    void ResumeTempPause() {
        if (tempPaused) {
            accumulatedPause += GetTickCount64() - pauseTime;
            tempPaused = false;
        }
    }
};

