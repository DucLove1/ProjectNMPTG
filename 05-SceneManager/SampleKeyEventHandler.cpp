#include "SampleKeyEventHandler.h"4

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"
#include "GameManager.h"
#include "Effect.h"
void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		if (mario->IsReachToExpectedSpeed())
		{
			mario->SetFlying(true);
		}
		else if (mario->GetLevel() == MARIO_LEVEL_TAIL && mario->IsFalling())
		{
			mario->SetSlowFalling(true);
		}
		break;

		//case DIK_Q:
		//	
		//	break;

	case DIK_Z:
		if (mario->GetLevel() == MARIO_LEVEL_TAIL)
			mario->SetState(MARIO_STATE_ATTACK);
		break;
	case DIK_X:
		mario->SetSmallJump();
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		mario->SetPowerUP(true);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_TAIL);
		mario->SetPowerUP(true);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_A:
		if (mario->GetLevel() == MARIO_LEVEL_TAIL)
		{
			if (!mario->IsSitting())
				mario->SetAttack(true);
		}
		break;
		//case DIK_8: //was test
		//	mario->SetPickUp(true);
		//	break;
	case DIK_R: // reset
		//Reload();
		break;
	case DIK_D:
		GameManager::GetInstance()->PauseGame();
		break;
	case DIK_C:
		GameManager::GetInstance()->ResumeGame();
		break;
	case DIK_Q:
		GameManager::GetInstance()->PauseToTransform();
		break;
	case DIK_E:
		GameManager::GetInstance()->ResumeWhenDoneTransform();
		break;
	case DIK_Y:
		float x, y;
		mario->GetPosition(x, y);
		Effect* effect = new Effect(x, y, EFFECT_DISAPPEAR);
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(effect); // add effect to scene)
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
	case DIK_X:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		mario->SetPickUp(false);
		//mario->SetAttack(false);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{

		if (game->IsKeyDown(DIK_A)) {
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		}
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A)) 
		{
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		}
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_Z))
	{
		if (mario->GetLevel() == MARIO_LEVEL_TAIL)
		{
			if (!mario->IsSitting()) 
			{
				mario->SetAttack(true);
			}
		}
	}
	else
	{
		mario->SetState(MARIO_STATE_IDLE);
	}
}