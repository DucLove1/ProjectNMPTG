#pragma once

#include "GameObject.h"
#include "FadeTransition.h"
/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 

	float width;
	float height;
	ULONGLONG time_start;
	FadeTransition* fade_transition;
	bool isTransited; // true if the scene start to transition, false otherwise
	bool isPortalIn; // true if this portal is for entering the scene, false if it's for exiting
public:
	CPortal(float l, float t, float r, float b, bool isPortalIn, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox(void);
	
	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 0; }
	void SwitchScene();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};