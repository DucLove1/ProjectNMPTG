#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"
#include "GameManager.h"
#include "Effect.h"
#include "FadeTransition.h"

float cdJumpByDIK_X = 0.0f;
float cdSlowFallingByDIK_X = 0.0f;

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (GameManager::GetInstance()->IsEndGame())
	{
		return;
	}
	switch (KeyCode)
	{
	case DIK_DOWN:
		if (mario->CanEntryPipe())
		{
			mario->SetForEntryPipeDown();
		}
		else
		{
			mario->SetState(MARIO_STATE_SIT);
		}
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		if(mario->IsOnDropLift())
		{
			float vx, vy;
			mario->GetSpeed(vx, vy);
			mario->SetSpeed(vx, 0);
		}
    if (mario->IsReadyToFly())
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
		//mario->SetForEndGame(true);
		break;
	case DIK_A:
		if (mario->GetLevel() == MARIO_LEVEL_TAIL)
		{
			if (!mario->IsSitting() && !mario->IsAttack())
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
	case DIK_T:
		float x, y;
		CGame::GetInstance()->GetCamPos(x, y);
		FadeTransition* fade = new FadeTransition(x, y, 2000);
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(fade);
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
		//testng
	case DIK_9:
		mario->SetForEndGame(false);
	}
}

void CSampleKeyHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_UP))
	{
		mario->SetUpArrow(true);
		mario->SetForEntryPipeUp();
	}
	else
	{
		mario->SetUpArrow(false);
	}
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
	else
	{
		mario->SetState(MARIO_STATE_IDLE);
	}

	if (game->IsKeyDown(DIK_Z))
	{
		if (mario->GetLevel() == MARIO_LEVEL_TAIL)
		{
			if (!mario->IsSitting())
			{
				if (!mario->IsAttack())
					mario->SetAttack(true);
			}
		}
	}
	if (game->IsKeyDown(DIK_X))
	{
		if (mario->GetLevel() == MARIO_LEVEL_TAIL && mario->IsReadyToFly())
		{
			mario->SetFlying(true);
		}
		if (mario->GetLevel() == MARIO_LEVEL_TAIL && mario->IsFalling())
		{
			if (cdSlowFallingByDIK_X <= 0.0f)
			{
				mario->SetSlowFalling(true);
				cdSlowFallingByDIK_X = 4.0f;
			}
			else
			{
				cdSlowFallingByDIK_X -= 1.0f;
			}
		}
		else if (!mario->IsSlowFalling())
		{
			/*
			if (mario->GetState() != MARIO_STATE_JUMP
				&& mario->GetState() != MARIO_STATE_RELEASE_JUMP
				&& mario->GetState() != MARIO_STATE_SMALL_JUMP )
			*/
			if (cdJumpByDIK_X <= 0.0f)
			{
				mario->SetSmallJump();
				cdJumpByDIK_X = 10.0f;
			}
			else
			{
				cdJumpByDIK_X -= 1.0f;
			}
			//DebugOut(L"%d \n", mario->GetJumpedTime());
		}
	}
}