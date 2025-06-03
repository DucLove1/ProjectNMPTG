#pragma once

#include "GameObject.h"
#include "FadeTransition.h"
/*
	Object that triggers scene switching
*/
#define NON_POS -1000.0f
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 

	float width;
	float height;
	ULONGLONG time_start;
	FadeTransition* fade_transition;
	bool isTransited; // true if the scene start to transition, false otherwise
	bool isPortalIn; // true if this portal is for entering the scene, false if it's for exiting
	float posOutX; // position mario go out in this scene which is also in the same world
	float posOutY; // position mario go out in this scene which is also in the same world
public:
	CPortal(float l, float t, float r, float b, bool isPortalIn, int scene_id, float posOutX = NON_POS, float posOutY = NON_POS);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox(void);
	
	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 0; }
	void SwitchScene();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetPosOut(float& x, float& y) 
	{ 
		x = posOutX; 
		y = posOutY; 
	}
	bool IsSetPosOut() 
	{ 
		return posOutX != NON_POS && posOutY != NON_POS; 
	}
};