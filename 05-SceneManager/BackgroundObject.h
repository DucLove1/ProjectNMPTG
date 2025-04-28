#pragma once
#include "GameObject.h"
class BackgroundObject : public CGameObject
{
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	int IsBlocking() { return 0; }
	int IsDirectionColliable(float nx, float ny) { return 0; }
public:
	BackgroundObject(float x, float y) : CGameObject(x, y) {};
};
// BackgroundObject is a special type of CGameObject that is not collidable and does not block other objects.
