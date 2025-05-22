#include "ItemGoldBrick.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "PlayScene.h"
#include "GameClock.h"
#include "GreenMushroom.h"
#include "RedMushroom.h"
#include "Koopa.h"
int ItemGoldBrick::ChooseItem()
{
	if (this->wayChooseItem == RANDOM_ITEM)
	{
		CMario* player = (CMario*)(((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer());
		int level = player->GetLevel();
		if (level == MARIO_LEVEL_SMALL)
			return RED_MUSHROOM;
		else return LEAF;
	}
	return GREEN_MUSHROOM;
}
void ItemGoldBrick::GoUp(DWORD dt)
{
	if (this->y - vy * dt <= minY)
	{
		this->y = minY;
		SetState(STATE_GO_DOWN);
	}
	else vy = VY;

}
void ItemGoldBrick::GoDown(DWORD dt)
{
	if (this->y + vy * dt >= maxY)
	{
		this->y = maxY;
		if (item1)
		{
			CGameObject* mario = ((LPPLAYSCENE)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer();
			float mX, mY;
			mario->GetPosition(mX, mY);
			int nx = (this->x <= mX) ? -1 : 1;
			dynamic_cast<CMushroom*>(item1)->GotHit(nx);
		}
		SetState(STATE_IDLE);
	}
	else vy = VY;
}
//void ItemGoldBrick::InitializeRedMushroom(LPCOLLISIONEVENT e)
//{
//	float mX, mY;
//	e->src_obj->GetPosition(mX, mY);
//	int direction = (mX < this->x) ? 1 : -1;
//	item = new RedMushroom(this->x, this->y, direction);
//	((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(item);
//}
//void ItemGoldBrick::InitializeGreenMushroom(LPCOLLISIONEVENT e)
//{
//	float mX, mY;
//	e->src_obj->GetPosition(mX, mY);
//	int direction = (mX < this->x) ? 1 : -1;
//	item = new GreenMushroom(this->x, this->y, direction);
//	((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(item);
//}
void ItemGoldBrick::InitializeLeaf(LPCOLLISIONEVENT e)
{
	item2 = new CLeaf(this->x, this->y);
	((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(item2);
	//xoa item1
	item1->Delete();
	item1 = nullptr;
}
void ItemGoldBrick::GotHit(LPCOLLISIONEVENT e)
{
	// chon item
	int itemId = ChooseItem();
	// tao vat pham
	if (this->active == true)
	{
		// cho brick chay len
		SetState(STATE_GO_UP);
		// chuyen ve inactive
		this->active = false;
		switch (itemId)
		{
		case RED_MUSHROOM:
		case GREEN_MUSHROOM:
		{
			break;
		}
		case LEAF:
			InitializeLeaf(e);
			break;
		default:
			break;
		}
		//this->SetState(INACTIVE);
	}

}

void ItemGoldBrick::Render()
{
	GoldBrick::Render();
}

void ItemGoldBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	switch (state)
	{
	case STATE_GO_UP:
		GoUp(dt);
		break;
	case STATE_GO_DOWN:
		GoDown(dt);
		break;
	case STATE_IDLE:
		vy = 0;
		break;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void ItemGoldBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!(state == STATE_GO_UP))
		return;
	if (dynamic_cast<Koopa*>(e->obj))
	{
		Koopa* koopa = dynamic_cast<Koopa*>(e->obj);
		koopa->KickedFromBottom(this);
	}
}
void ItemGoldBrick::OnNoCollision(DWORD dt)
{
	if (state == STATE_GO_UP)
	{
		y -= vy * dt;
		if (y <= minY)
			y = minY;
	}
	else {
		y += vy * dt;
		if (y >= maxY)
			y = maxY;
	}
}
