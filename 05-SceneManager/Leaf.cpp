#include "Leaf.h"
#include "debug.h"

#define PI 3.14159f

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//let leaf lauch before it fall
	if (gotFirstForce == false && y > firstForceHeight)
	{
		vy = -LEAF_SPEED * 2;
	}
	else
	{
		canRender = false;
		gotFirstForce = true;
		vy = LEAF_SPEED;
	}

	//set speed vx
	if (!gotFirstForce)
	{
		vx = 0;
	}
	else if (nx >= 0)
	{
		vx = LEAF_SPEED;
		if (preNx * nx < 0)
			firstForceHeight = y;
	}
	else if (nx < 0)
	{
		vx = -LEAF_SPEED;
		if (preNx * nx < 0)
			firstForceHeight = y;
	}

	preNx = nx;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLeaf::Render()
{
	//set animation
	if (canRender)
	{
		if (nx > 0 && x >= offSetRightX)
		{
			nx = -1;
		}
		else if (nx < 0 && x <= offSetLeftX)
		{
			nx = 1;
		}

		CAnimations* animations = CAnimations::GetInstance();
		if (nx >= 0)
			animations->Get(ID_ANI_LEAF_LEFT)->Render(x, y);
		else
			animations->Get(ID_ANI_LEAF_RIGHT)->Render(x, y);
	}
	canRender = !canRender;
	//RenderBoundingBox();
}
void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CLeaf::OnNoCollision(DWORD dt)
{
	if (gotFirstForce == false)
	{
		y += vy * dt;
		return;
	}

	if (nx >= 0)
	{
		x += vx * dt;
		if (x >= offSetRightX)
		{
			x = offSetRightX;
		}
		float dy = (sin((x - offSetLeftX) / 8 - PI / 2) + 1) * 20 / 3.0f;

		y = firstForceHeight + dy;

	}
	else
	{
		x += vx * dt;
		if (x <= offSetLeftX)
		{
			x = offSetLeftX;
		}
		float dy = ((sin((x - offSetLeftX) / 8 + 3 * PI / 2 - 4)) + 1) * 20 / 3.0f;

		y = firstForceHeight + dy;
	}
}