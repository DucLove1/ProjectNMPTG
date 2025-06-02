#include "RedKoopa.h"
#define MAX_VY 0.1f
void RedKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (vx == 0)
		this->comboScoreSystem->Reset();
	/*vy += ay * dt;*/
	if (!onGround)
	{
		vy += ay * dt;
	}
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
	vx = 0;
	vy = MAX_VY * sin( 2 * GameClock::GetInstance()->GetTime() / 1000.0f);
}

void RedKoopa::UpdateStateHasNoWing()
{

}

