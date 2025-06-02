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
	vy = -SPEED_Y; // di chuyen len tren
	if (this->y - dt * SPEED_Y <= this->minY)
	{
		this->y = this->minY;
		SetState(STATE_GO_DOWN);
	}
}
void ItemGoldBrick::GoDown(DWORD dt)
{
	vy = VY;
	if (this->y + SPEED_Y* dt >= maxY)
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
		vy = 0;
	}
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
		this->isBouncing = true;
		// chuyen ve inactive
		this->active = false;
		switch (itemId)
		{
		case RED_MUSHROOM:
		case GREEN_MUSHROOM:
			break;
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
	if (this->isBouncing == false && this->active == false && doneHit == false)
	{
		doneHit = true;
	}
	if (!doneHit)
		return;
	if (item1)
	{
		CGameObject* mario = ((LPPLAYSCENE)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer();
		float mX, mY;
		mario->GetPosition(mX, mY);
		int nx = (this->x <= mX) ? -1 : 1;
		dynamic_cast<CMushroom*>(item1)->GotHit(nx);
		item1 = nullptr;
	}
}

//void ItemGoldBrick::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//	if (state == STATE_GO_UP)
//	{
//		Koopa* koopa = dynamic_cast<Koopa*>(e->obj);
//		if (koopa != nullptr)
//			koopa->KickedFromBottom(this); // koopa bi brick hit len tren
//	}
//}
//void ItemGoldBrick::OnNoCollision(DWORD dt)
//{
//	this->y += vy * dt;
//}
