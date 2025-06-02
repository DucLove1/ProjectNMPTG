#include "BouncingCoin.h"
#include "Effect.h"
#include "PlayScene.h"
#include "GameManager.h"
void CBouncingCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (wasReachToHeightBrace)
	{
		vy = FORCE;
	}

	y += vy * dt;
	if (y <= brace)
	{
		wasReachToHeightBrace = true;
	}
	if (y > begin)
	{
		Effect* effect = new Effect(x, y, EFFECT_100);
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(effect);
		GameManager::GetInstance()->AddScore(100);
		this->Delete();
	}

	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBouncingCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(23001/*ID_ANI_BOUNCING_COIN*/)->Render(x, y);
}