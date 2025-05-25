#include "Venus.h"
#include "Animations.h"
#include "GameClock.h"
#include "PlayScene.h"
#include "Effect.h"
#define DIFF_FROM_HEAD_RED 8.0f
#define DIFF_FROM_HEAD_GREEN 5.0f
void Venus::FollowMario()
{
	float marioX, marioY;
	mario->GetPosition(marioX, marioY);
	float x, y;
	this->GetPosition(x, y);
	nx = (marioX < x) ? -1 : 1;
	ny = (marioY < y - DIFF_FROM_HEAD_RED) ? -1 : 1;
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
			aniId = (type == RED) ? ID_ANI_RED_VENUS_RIGHT_DOWN_FIRE : ID_ANI_GREEN_VENUS_RIGHT_DOWN_FIRE;
			break;
		case 2:
			aniId = (type == RED) ? ID_ANI_RED_VENUS_LEFT_DOWN_FIRE : ID_ANI_GREEN_VENUS_LEFT_DOWN_FIRE;
			break;
		case 3:
			aniId = (type == RED) ? ID_ANI_RED_VENUS_LEFT_UP_FIRE : ID_ANI_GREEN_VENUS_LEFT_UP_FIRE;
			break;
		case 4:
			aniId = (type == RED) ? ID_ANI_RED_VENUS_RIGHT_UP_FIRE : ID_ANI_GREEN_VENUS_RIGHT_UP_FIRE;
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
			aniId = (type == RED) ? ID_ANI_RED_VENUS_RIGHT_DOWN : ID_ANI_GREEN_VENUS_RIGHT_DOWN;
			break;
		case 2:
			aniId = (type == RED) ? ID_ANI_RED_VENUS_LEFT_DOWN : ID_ANI_GREEN_VENUS_LEFT_DOWN;
			break;
		case 3:
			aniId = (type == RED) ? ID_ANI_RED_VENUS_LEFT_UP : ID_ANI_GREEN_VENUS_LEFT_UP;
			break;
		case 4:
			aniId = (type == RED) ? ID_ANI_RED_VENUS_RIGHT_UP : ID_ANI_GREEN_VENUS_RIGHT_UP;
			break;
		}
	}
	break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
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
			timer = GameClock::GetInstance()->GetTime();
		else if (GameClock::GetInstance()->GetTime() - timer > TIME_WAIT_TO_FIRE)
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
		timer = GameClock::GetInstance()->GetTime();
		float angle = ChooseAngle();
		if (type == RED)
			bullet->Fire(x, y - DIFF_FROM_HEAD_RED, angle);
		else
			bullet->Fire(x, y - DIFF_FROM_HEAD_GREEN, angle);
	}
	else if (GameClock::GetInstance()->GetTime() - timer > TIME_WAIT_TO_HIDE)
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
		if (timer == -1)
			timer = GameClock::GetInstance()->GetTime();
		else 
		{
			float marioX, marioY;
			mario->GetPosition(marioX, marioY);
			// mario is close to Venus, Venus doesn't appear
			if (abs(marioX - this->x) <= DISTANCE_TO_APPEAR)
				return;
			if (GameClock::GetInstance()->GetTime() - timer > TIME_WAIT_TO_APPEAR)
			{
				SetState(APPEAR);
				timer = -1;
			}
		}
	}
}
float Venus::ChooseAngle()
{
	//calculate the angle between the center of the Venus and the Mario
	float marioX, marioY;
	mario->GetPosition(marioX, marioY);
	float deltaX = abs(marioX - this->x);
	float deltaY = abs(marioY - (type == RED) ? (this->y - DIFF_FROM_HEAD_RED) : (this->y - DIFF_FROM_HEAD_GREEN));
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
	// check the special angles
	int quadrant = FindQuardrant();
	if(angle < angles[quadrant - 1][0])
	{
		res = angles[quadrant - 1][0];
	}
	else if(angle > angles[quadrant - 1][1])
	{
		res = angles[quadrant - 1][1];
	}
	else
	{
		/*res = (abs(angle - angles[quadrant - 1][0]) <= abs(angle - angles[quadrant - 1][1])) 
			? angles[quadrant - 1][0] : angles[quadrant - 1][1];*/
		res = angles[quadrant - 1][1];
	}
	return res;
}
void Venus::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (type == RED)
	{
		l = x - RED_BBOX_WIDTH / 2;
		t = y - RED_BBOX_HEIGHT / 2;
		r = l + RED_BBOX_WIDTH;
		b = t + RED_BBOX_HEIGHT;
	}
		else
	{
		l = x - GREEN_BBOX_WIDTH / 2;
		t = y - GREEN_BBOX_HEIGHT / 2;
		r = l + GREEN_BBOX_WIDTH;
		b = t + GREEN_BBOX_HEIGHT;
	}
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

void Venus::KickedFromBottom(CGameObject* obj)
{
	KnockedOut(obj);
}

void Venus::KnockedOut(CGameObject* obj)
{
	Effect* effect = new Effect(x, y - 10, EFFECT_DISAPPEAR);
	dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene())->AddObject(effect);
	Delete();
}
