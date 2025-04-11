#include "CQuestionBrick.h"

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	if (cdHit >= 0) {
		cdHit -= dt;
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
void CQuestionBrick::GotHit()
{
	if (timeCanHit <= 0) return;
	if(cdHit <= 0) // can do 
	{
		timeCanHit--;
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		CGoomba* goomba = new CGoomba(x, y - 16);
		scene->AddObject(goomba);
		cdHit = 1000;
	}
}

void CQuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	int type = GetTypeOfHolder();

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

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}

void CQuestionBrick::GetBoundingBox( float &l, float &t, float &r, float &b) {
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}