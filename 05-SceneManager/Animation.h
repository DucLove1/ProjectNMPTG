#pragma once

#include <Windows.h>
#include <unordered_map>

#include "Sprites.h"
#include "AnimationFrame.h"
#include "GameObject.h"
using namespace std;

class CAnimation
{
	ULONGLONG lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime = 100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	bool CheckObjectPause(CGameObject* object);
	void Render(float x, float y);
	bool Done() { return currentFrame == frames.size() - 1; }
	void Reset() { currentFrame = -1; lastFrameTime = -1; }
	void SetAllFrameTime(DWORD time);
};

typedef CAnimation* LPANIMATION;