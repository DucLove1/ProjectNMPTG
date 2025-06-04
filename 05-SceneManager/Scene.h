#pragma once

#include "KeyEventHandler.h"
#define NONE_POS -1000
/*
*  Abstract class for a game scene
*/
class CScene
{
protected:
	LPKEYEVENTHANDLER key_handler;
	int id;
	LPCWSTR sceneFilePath;
	int worldIndex;
	float posOutX; // position mario go out in this scene which is also in the same world
	float posOutY; // position mario go out in this scene which is also in the same world
public: 
	CScene(int id, LPCWSTR filePath, int worldIndex)
	{
		this->id = id;
		this->sceneFilePath = filePath;
		this->key_handler = NULL;
		this->worldIndex = worldIndex;
		this->posOutX = NONE_POS;
		this->posOutY = NONE_POS;
	}

	LPKEYEVENTHANDLER GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0; 
	int GetWordIndex() { return worldIndex; }
	void SetPosOut(float x, float y) 
	{ 
		this->posOutX = x; 
		this->posOutY = y; 
	}
};
typedef CScene * LPSCENE;


class CSceneKeyHandler : public CKeyEventHandler
{
protected: 
	CScene * scence; 

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CSceneKeyHandler(LPSCENE s) :CKeyEventHandler() { scence = s; }
};

typedef CSceneKeyHandler* LPSCENEKEYHANDLER;