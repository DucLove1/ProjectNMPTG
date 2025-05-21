#pragma once
#include "GameObject.h"
#define GRAVITY 0.001f
#define AX 0.00009f
#define START_VY_TOP 0.3f
#define START_VY_BOTTOM 0.2f
class ParticalBreak: public CGameObject
{
private:
	int type;
	ULONGLONG timer_delete;
	float ay;
	float ax;
	public:
		ParticalBreak(float x, float y, int type) : CGameObject(x, y)
		{
			this->type = type;
			timer_delete = GetTickCount64();
			ay = GRAVITY;
			ax = (type == TYPE::UP_LEFT || type == TYPE::DOWN_LEFT) ? -AX : AX; // set ax based on type)
			vx = 0;
			if(type == TYPE::UP_LEFT || type == TYPE::UP_RIGHT)
			{
				vy = -START_VY_TOP;
			}
			else
			{
				vy = -START_VY_BOTTOM;
			}
		}
		int IsCollidable() override;
		void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
		void Render() override;
		void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) override;
		void OnNoCollision(DWORD dt) override;
	enum TYPE
	{
		UP_LEFT,
		UP_RIGHT,
		DOWN_LEFT,
		DOWN_RIGHT,
	};
};

