#pragma once
#include "GameObject.h"
#include "ParticalBreak.h"
#include "PlayScene.h"
class EffectBreak 
{
public:
	EffectBreak(float x, float y) 
	{
		LPPLAYSCENE curScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
		ParticalBreak* particalBreak1 = new ParticalBreak(x-4, y-5, ParticalBreak::TYPE::UP_LEFT);
		ParticalBreak* particalBreak2 = new ParticalBreak(x+4, y-5, ParticalBreak::TYPE::UP_RIGHT);
		ParticalBreak* particalBreak3 = new ParticalBreak(x-4, y+5, ParticalBreak::TYPE::DOWN_LEFT);
		ParticalBreak* particalBreak4 = new ParticalBreak(x+4, y+5, ParticalBreak::TYPE::DOWN_RIGHT);
		curScene->AddObject(particalBreak1);
		curScene->AddObject(particalBreak2);
		curScene->AddObject(particalBreak3);
		curScene->AddObject(particalBreak4);
		delete(this);
	}
};

