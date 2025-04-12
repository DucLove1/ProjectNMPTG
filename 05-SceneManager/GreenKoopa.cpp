#include "GreenKoopa.h"

void GreenKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx += ax * dt;
	if (!onGround)
	{
		vy += ay * dt;
	}
	else
		vy = 0;
	switch (state)
	{
	case HAS_WING:
		UpdateStateHasWing();
		break;
	case HAS_NO_WING:
		UpdateStateHasNoWing();
		break;
	case IN_SHELL_UP:
	case IN_SHELL_DOWN:
		UpdateStateInShell();
		break;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void GreenKoopa::UpdateStateHasWing()
{
	if (this->onGround)
	{
		vy = -KOOPA_JUMP_FORCE;
	}
}

void GreenKoopa::UpdateStateHasNoWing()
{

}

