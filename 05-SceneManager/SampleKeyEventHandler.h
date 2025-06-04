#pragma once

#include "Scene.h"

extern float cdJumpByDIK_X;
extern float cdSlowFallingByDIK_X;

class CSampleKeyHandler: public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CSampleKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};
