#include "ItemGoldBrick.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "PlayScene.h"
#include "GameClock.h"
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
void ItemGoldBrick::InitializeRedMushroom(LPCOLLISIONEVENT e)
{
	float mX, mY;
	e->src_obj->GetPosition(mX, mY);
	int direction = (mX < this->x) ? 1 : -1;
	item = new CMushroom(this->x, this->y, direction);
	((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(item);
}
void ItemGoldBrick::InitializeLeaf(LPCOLLISIONEVENT e)
{
	item = new CLeaf(this->x, this->y);
	((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(item);
}
void ItemGoldBrick::GotHit(LPCOLLISIONEVENT e)
{
	// chon item
	int itemId = RED_MUSHROOM;
	// tao vat pham
	if (item == NULL && this->active == true)
	{
		// chuyen ve inactive
		this->active = false;
		switch (itemId)
		{
		case RED_MUSHROOM:
			InitializeRedMushroom(e);
			break;
		case GREEN_MUSHROOM:

			break;
		case LEAF:
			InitializeLeaf(e);
			break;
		default:
			break;
		}
		this->SetState(INACTIVE);
	}

}

void ItemGoldBrick::Render()
{
	if (item != NULL && !item->IsDeleted() && 
		!GameClock::GetInstance()->IsPaused()  && 
		!GameClock::GetInstance()->IsTempPaused())
	{
		item->Render();
	}
	GoldBrick::Render();
}
