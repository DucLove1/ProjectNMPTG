#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "CQuestionBrick.h"
class CEnemy : public CGameObject
{
	protected:
	float ax;
	float ay;
	bool onGround;
public:
	CEnemy(float x, float y) : CGameObject(x, y)
	{
		this->ay = 0.001f;
		this->ax = 0;
		this->vx = 0;
		this->onGround = false;
	}
	virtual int IsCollidable() {return 1;}
	virtual int IsBlocking() { return 0; }
	virtual void KickedFromTop(CGameObject*) {};
	virtual void KnockedOut(CGameObject*) {};
	virtual void TouchTwoSide(CGameObject*) {};
	virtual bool IsAlive() { return true; };
	void SetAccelation(float ax, float ay) 
		{ this->ax = ax; this->ay = ay; }
};

