#include "Venus.h"
#include "Animations.h"
void Venus::FollowMario()
{
	float marioX, marioY;
	mario->GetPosition(marioX, marioY);
	float x, y;
	this->GetPosition(x, y);
	nx = (marioX < x) ? -1 : 1;
	ny = (marioY < y) ? -1 : 1;
}

void Venus::Render()
{
	// Render the Venus sprite based on its state
	int aniId = ID_ANI_RED_VENUS_LEFT_UP;
	switch (state)
	{
	case ATTACKING:
	{
		int quarant = FindQuardrant();
		switch (quarant)
		{
		case 1:
			aniId = ID_ANI_RED_VENUS_RIGHT_UP_FIRE;
			break;
		case 2:
			aniId = ID_ANI_RED_VENUS_LEFT_UP_FIRE;
			break;
		case 3:
			aniId = ID_ANI_RED_VENUS_LEFT_DOWN_FIRE;
			break;
		case 4:
			aniId = ID_ANI_RED_VENUS_RIGHT_DOWN_FIRE;
			break;
		}
	}
	break;
	case WAITING:
	{
		int quadrant = FindQuardrant();
		switch (quadrant)
		{
		case 1:
			aniId = ID_ANI_RED_VENUS_RIGHT_UP;
			break;
		case 2:
			aniId = ID_ANI_RED_VENUS_LEFT_UP;
			break;
		case 3:
			aniId = ID_ANI_RED_VENUS_LEFT_DOWN;
			break;
		case 4:
			aniId = ID_ANI_RED_VENUS_RIGHT_DOWN;
			break;
		}
	}
	break;
	case KNOCKED_OUT:
		// Render knocked out sprite
		break;
	default:
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}
int Venus::FindQuardrant()
{
	if (ny == -1)
	{
		if (nx == -1)
			return 2;
		else return 1;
	}
	else
	{
		if (nx == -1)
			return 3;
	}
	return 4;
}
void Venus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void Venus::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

void Venus::SetState(int state)
{
}
