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
	cur_quarant = FindQuardrant();
	switch (state)
	{
	case ATTACK:
	{
		switch (cur_quarant)
		{
		case 1:
			aniId = ID_ANI_RED_VENUS_RIGHT_DOWN_FIRE;
			break;
		case 2:
			aniId = ID_ANI_RED_VENUS_LEFT_DOWN_FIRE;
			break;
		case 3:
			aniId = ID_ANI_RED_VENUS_LEFT_UP_FIRE;
			break;
		case 4:
			aniId = ID_ANI_RED_VENUS_RIGHT_UP_FIRE;
			break;
		}
	}
	break;
	case APPEAR:
	case HIDE:
	{
		switch (cur_quarant)
		{
		case 1:
			aniId = ID_ANI_RED_VENUS_RIGHT_DOWN;
			break;
		case 2:
			aniId = ID_ANI_RED_VENUS_LEFT_DOWN;
			break;
		case 3:
			aniId = ID_ANI_RED_VENUS_LEFT_UP;
			break;
		case 4:
			aniId = ID_ANI_RED_VENUS_RIGHT_UP;
			break;
		}
	}
	break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}
int Venus::FindQuardrant()
{
	if(this->state == ATTACK)
		return cur_quarant;
	FollowMario();
	if (ny == -1)
	{
		if (nx == -1)
			return 3;
		else return 4;
	}
	else
	{
		if (nx == -1)
			return 2;
	}
	return 1;
}
void Venus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	switch (state)
	{
	case APPEAR:
		UpdateStateAppear(dt);
		break;
	case ATTACK:
		UpdateStateAttack(dt);
		break;
	case HIDE:
		UpdateStateHide(dt);
		break;
	}
}
void Venus::UpdateStateAppear(DWORD dt)
{
	if (this->y - SPEED_Y * dt > minY)
	{
		this->y -= SPEED_Y * dt;
	}
	else
	{
		this->y = minY;
		if (timer == -1)
			timer = GetTickCount64();
		else if (GetTickCount64() - timer > TIME_WAIT_TO_FIRE)
		{
			SetState(ATTACK);
			timer = -1;
		}
	}
}
void Venus::UpdateStateAttack(DWORD dt)
{
	if (timer == -1)
	{
		timer = GetTickCount64();
		float angle = ChooseAngle();
		bullet->Fire(x,y - 4.5f,angle);
	}
	else if (GetTickCount64() - timer > TIME_WAIT_TO_HIDE)
	{
		SetState(HIDE);
		timer = -1;
	}
}
void Venus::UpdateStateHide(DWORD dt)
{
	if (this->y + SPEED_Y * dt < maxY)
	{
		this->y += SPEED_Y * dt;
	}
	else
	{
		this->y = maxY;
		float marioX, marioY;
		mario->GetPosition(marioX, marioY);
		// mario is close to Venus, Venus doesn't appear
		if (abs(marioX - this->x) <= DISTANCE_TO_APPEAR)
			return;
		if (timer == -1)
			timer = GetTickCount64();
		else if (GetTickCount64() - timer > TIME_WAIT_TO_APPEAR)
		{
			SetState(APPEAR);
			timer = -1;
		}
	}
}
float Venus::ChooseAngle()
{
	//calculate the angle between the center of the Venus and the Mario
	float marioX, marioY;
	mario->GetPosition(marioX, marioY);
	float deltaX = abs(marioX - this->x);
	float deltaY = abs(marioY - (this->y-4.5f));
	float angle = atan2f(deltaY, deltaX) * 180 / 3.14;
	// normalize the angle to be in the range of [0, 360)
	switch (cur_quarant)
	{
	case 1:
		break;
	case 2:
		angle = 180 - angle;
		break;
	case 3:
		angle = 180 + angle;
		break;
	case 4:
		angle = 360 - angle;
		break;
	}
	int res = 0;
	float curDiff;
	float minDiff = INT_MAX;
	for (int& curAngle : angles)
	{
		curDiff = abs(angle - curAngle);
		if (curDiff < minDiff)
		{
			minDiff = curDiff;
			res = curAngle;
		}
	}
	return res;
}
void Venus::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BBOX_WIDTH / 2;
	t = y - BBOX_HEIGHT / 2;
	r = l + BBOX_WIDTH;
	b = t + BBOX_HEIGHT;
}

void Venus::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case HIDE:
		// Set waiting state
		this->state = HIDE;
		break;
	case ATTACK:
		// Set attacking state
		this->state = ATTACK;
		break;
	case APPEAR:
		// Set knocked out state
		this->state = APPEAR;
		break;
	default:
		break;
	}
}
