#include "Leaf.h"
#include "debug.h"

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//let leaf lauch before it fall
	if (gotFirstForce == false && y > firstForceHeight)
	{
		vy = -LEAF_SPEED * 2;
	}
	else
	{
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
	}
	else if (nx < 0)
	{
		vx = -LEAF_SPEED;
	}

	x += vx * dt;
	y += vy * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLeaf::Render()
{
	//set animation
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
	RenderBoundingBox();
}
void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}
