#include "ItemGoldBrick.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "PlayScene.h"
void ItemGoldBrick::InitializeRedMushroom(LPCOLLISIONEVENT e)
{
	float mX, mY;
	e->obj->GetPosition(mX, mY);
	int direction;
	if (mX < this->x)
	{
		direction = 1;
	}
	else 
	{
		direction = -1;
	}
	item = new CMushroom(this->x, this->y, direction);
	((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(item);
}
void ItemGoldBrick::InitializeLeaf(LPCOLLISIONEVENT e)
{
	item = new CLeaf(this->x, this->y);
}
void ItemGoldBrick::GotHit(LPCOLLISIONEVENT e)
{
	// chuyen ve inactive
	// tao vat pham
		if (item == NULL && this->active == true)
		{
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
	if(item != NULL && !item->IsDeleted())
	{
		item->Render();
	}
	GoldBrick::Render();
}
