#include "CQuestionBrick.h"
#include "GameClock.h"
#include "GameManager.h"
#include "RedMushroom.h"

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	if (cdHit >= 0) {
		cdHit -= dt;
	}
	switch (state)
	{
	case STATE_GO_UP:
		GoUp(dt);
		break;
	case STATE_GO_DOWN:
		GoDown(dt);
		break;

	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CQuestionBrick::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CQuestionBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//CMario* mario = dynamic_cast<CMario*>(e->obj);

	//if (e->ny > 0) 
	//{
	//	if (mario->GetState() == MARIO_STATE_JUMP)
	//	{
	//		if (this->timeCanHit > 0)
	//		{
	//			cdAnim = GetTickCount64();
	//			CGoomba* goomba = new CGoomba(x, y);
	//			timeCanHit--;
	//		}
	//	}
	//}
	//else if (e->ny == 0)
	//{
	//	// This temp code for SPIN TAIL but have not been define yet
	//	if (mario->GetState() == MARIO_STATE_JUMP) //spintail
	//	{
	//		if (timeCanHit > 0)
	//		{
	//			cdAnim = GetTickCount64();
	//			timeCanHit--;
	//		}
	//	}

	//}
}
void CQuestionBrick::GotHit(LPCOLLISIONEVENT e)
{

	if (timeCanHit <= 0) return;
	if (cdHit <= 0) // can do 
	{
		timeCanHit--;
		SetState(STATE_GO_UP);
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

		////if (dynamic_cast<CMario*>(e->obj) == NULL) return;
		//CMario* mario = (CMario*)e;
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();


		if (typeOfHolder == COIN_ITEM)
		{
			//GameManager::GetInstance()->AddScore(1000);
			CBouncingCoin* coin = new CBouncingCoin(x, y - 16);
			scene->AddObject(coin);
			GameManager::GetInstance()->PlusCoins(1);
		}
		else {
			//CMushroom* mr = new CMushroom(x, y, nx);
			if (mario->GetLevel() == MARIO_LEVEL_SMALL)
			{
				// vi khi hit thi brick se chay len xuong, neu cho item cung vi tri voi cuc gach thi se bi lo cuc nam
				/*this->item = new RedMushroom(x, y - 8, nx);
				scene->AddObject(item);*/
			}
			else// if (mario->GetLevel() == MARIO_LEVEL_BIG)
			{
				this->item2 = new CLeaf(x, y);
				scene->AddObject(item2);
				// xoa item1
				if (this->item1 != nullptr)
					this->item1->Delete();
				this->item1 = nullptr;
			}
		}
		cdHit = CD_GOT_HIT;
	}
}

void CQuestionBrick::GoUp(DWORD dt)
{
	if (this->y - SPEED_Y * dt > minY)
	{
		this->vy = -SPEED_Y;
	}
	else
	{
		this->y = minY;
		SetState(STATE_GO_DOWN);
	}
}

void CQuestionBrick::GoDown(DWORD dt)
{
	if (this->y + SPEED_Y * dt < maxY)
	{
		this->vy = SPEED_Y;
	}
	else
	{
		this->y = maxY;
		this->vy = 0;
		if (item1 != nullptr && dynamic_cast<CMushroom*>(item1))
		{
			CGameObject* mario = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			float mX, mY;
			mario->GetPosition(mX, mY);
			int nx = (this->x <= mX) ? -1 : 1;
			dynamic_cast<CMushroom*>(item1)->GotHit(nx);
		}
		SetState(STATE_IDLE);
	}
}

void CQuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	int type = 1;// GetTypeOfHolder();

	switch (type)
	{
	case COIN_ITEM:
		aniId = ID_ANI_QUESTION_BRICK_COIN;
		break;
	case MUSHROOM_ITEM:
		aniId = ID_ANI_QUESTION_BRICK_MUSHROOM;
		break;
	case LEAF_ITEM:
		aniId = ID_ANI_QUESTION_BRICK_LEAF;
		break;
	default:
		aniId = ID_ANI_QUESTION_BRICK_SPIN;
		break;
	}
	if (timeCanHit <= 0) {
		aniId = ID_ANI_QUESTION_BRICK_EMPTY;
	}

	//if (item != NULL && !item->IsDeleted() &&
	//	!GameClock::GetInstance()->IsPaused() &&
	//	!GameClock::GetInstance()->IsTempPaused()&&
	//	(dynamic_cast<CLeaf*>(item) || dynamic_cast<CMushroom*>(item)))
	//	item->Render();
	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}