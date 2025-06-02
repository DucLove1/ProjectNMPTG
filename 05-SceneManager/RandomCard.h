#pragma once
#include "GameObject.h"
#define ACTIVE 1
#define INACTIVE 0
#define WIDTH 20
#define HEIGHT 22
class RandomCard: public CGameObject
{
	private:
	int cardID; // 0, 1, 2
public:
	RandomCard(float x, float y) : CGameObject(x, y)
	{
		this->cardID = -1;
		this->state = ACTIVE;

	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) override;
	void Render() override;
	int IsCollidable() override { return 0; }
	int IsBlocking() override { return 0; }
	void Touched();

};

