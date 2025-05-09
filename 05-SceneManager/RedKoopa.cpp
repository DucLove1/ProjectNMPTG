#include "RedKoopa.h"

void RedKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx += ax * dt;
	vy += ay * dt;
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
		UpdateStateInShell(dt);
		break;
	case KNOCK_OUT:
		UpdateStateKnockOut(dt);
		break;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void RedKoopa::UpdateStateHasWing()
{
}

void RedKoopa::UpdateStateHasNoWing()
{

}

