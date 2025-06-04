class DropLift;
#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "DropLift.h"

#include "debug.h"
#include "GameManager.h"

#define MARIO_WALKING_SPEED		0.15f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_EXPECTED_SPEED	0.175f

#define MARIO_ACCEL_WALK_X	0.00025f
#define MARIO_ACCEL_RUN_X	0.00035f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.0015f
#define MARIO_ACCEL_JUMP	0.00266666666666666f
#define MARIO_FRICTION	0.0002f
#define MARIO_MAX_JUMP_TIME 200

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_SPEED_ENTRY_PIPE 0.05f

#define FLYING_TIME 120;
#define FLYING_SCALE -0.2f
#define TIME_TO_CHARGE 2000.0f //~2 seconds

#define SLOW_FALLING_TIME 150
#define SLOW_FALLING_SCALE 0.1f
//#define CD_FLYING_TIME 50


#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301
#define MARIO_STATE_SMALL_JUMP		302

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_ATTACK			650

#define MARIO_STATE_SLOW_FALLING 	660
#define MARIO_MAX_FALLING_SPEED	0.2f

#define MARIO_STATE_POWERUP		700
#define MARIO_STATE_ENDGAME	1000

#define MARIO_STATE_PREPARE_ENTRY_PIPE		1050
#define MARIO_STATE_ENTRY_PIPE	1100

#define MARIO_MTIME_ONAIR		450


#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_TAIL	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_ENTRY_PIPE_DISTANCE 6

#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_RECOVERY_TIME 2500
#define MARIO_HIDDEN_GAP_WHILE_RECOVERY 200

#define MARIO_DELAY_TIME_WHILE_ANCHOR_ON_AIR_TAIL 500
#define MARIO_DELAY_TIME_WHILE_ANCHOR_ON_AIR 950

#pragma region MARIO_ANI_TYPE

#define  ANI_MARIO_IDLE_RIGHT 0
#define  ANI_MARIO_IDLE_LEFT 1
#define  ANI_MARIO_WALKING_RIGHT 2
#define  ANI_MARIO_WALKING_LEFT 3
#define  ANI_MARIO_RUNNING_RIGHT 4
#define  ANI_MARIO_RUNNING_LEFT 5
#define  ANI_MARIO_JUMP_WALK_RIGHT 6
#define  ANI_MARIO_JUMP_WALK_LEFT 7
#define  ANI_MARIO_JUMP_RUN_RIGHT 8 
#define  ANI_MARIO_JUMP_RUN_LEFT 9
#define  ANI_MARIO_BRACE_RIGHT 10
#define  ANI_MARIO_BRACE_LEFT 11
#define  ANI_MARIO_PICKING_IDLE_RIGHT 12
#define  ANI_MARIO_PICKING_IDLE_LEFT 13
#define  ANI_MARIO_PICKING_WALK_RIGHT 14
#define  ANI_MARIO_PICKING_WALK_LEFT 15
#define  ANI_MARIO_PICKING_RUN_RIGHT 16
#define  ANI_MARIO_PICKING_RUN_LEFT 17
#define  ANI_MARIO_PICKING_JUMP_RIGHT 18
#define  ANI_MARIO_PICKING_JUMP_LEFT 19
#define  ANI_MARIO_PICKING_RUN_JUMP_RIGHT 20
#define  ANI_MARIO_PICKING_RUN_JUMP_LEFT 21
#define  ANI_MARIO_SIT_RIGHT 22
#define  ANI_MARIO_SIT_LEFT 23
#define	 ANI_MARIO_POWER_UP_RIGHT 24
#define  ANI_MARIO_POWER_UP_LEFT 25
#define  ANI_MARIO_SLOWFALLING_RIGHT 26
#define  ANI_MARIO_SLOWFALLING_LEFT 27
#define  ANI_MARIO_ATTACK_RIGHT 28
#define  ANI_MARIO_ATTACK_LEFT 29
#define  ANI_MARIO_FLYING_RIGHT 30
#define  ANI_MARIO_FLYING_LEFT 31
#define  ANI_MARIO_ENTRY_PIPE 32
#pragma endregion

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level;

	float fdt;
	int untouchable;
	ULONGLONG untouchable_start;

	BOOLEAN isOnPlatform;
	//ULONGLONG jump_start;

	BOOLEAN isPickUp;

	int isRecovering;
	ULONGLONG recovery_start;

	bool isPowerUp;
	//bool isSelfPausing;
	ULONGLONG anchor_start; // time to anchor on air 

	int jumpedTime;
	bool isSlowFalling;
	int slowFallingTime;

	bool isFlying;
	int flyingTime;
	int startFlying;
	float powerUnit;
	float maxPowerUnit;

	bool upArrowWasHolded;
	bool canEntryPipe;
	bool isEntryPipe;
	bool isPrepareEntry;
	pair<float, float> targetPoint;

	//bool isLinkedLeft; // link to platform moving left direction
	//bool isLinkedUp; // link to platform moving up direction
	bool isLinked; //Both r has the same logic, so just 1 var to check it

	bool isEndGame;

	int coin;

	DropLift* movingPlatform;
	LPGAMEOBJECT item;
	LPGAMEOBJECT tail;
	int preNx;
	bool isEntryDown; /// for set vy direction

	void LimitByCameraBorder();

	void OnCollisionWithPipe(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBall(LPCOLLISIONEVENT e);
	void OnCollisionWithVenus(LPCOLLISIONEVENT e);
	void OnCollisionWithSpawnGate(LPCOLLISIONEVENT e);
	void OnCollisionWithGoldBrick(LPCOLLISIONEVENT e);
	void OnColliionWithDropLift(LPCOLLISIONEVENT e);

	int ConvertAniTypeToAniId(int animation_type);
	

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;

		//level = MARIO_LEVEL_SMALL;
		//this line is get level from GameManager because of saving level
		level = GameManager::GetInstance()->GetCurLevel();

		untouchable = 0;
		untouchable_start = -1;

		isRecovering = 0;
		recovery_start = -1;

		isPowerUp = false;
		//isSelfPausing = false;
		anchor_start = -1;

		isSlowFalling = false;
		jumpedTime = 0;
		isFlying = false;
		powerUnit = 0.0f; 
		maxPowerUnit = TIME_TO_CHARGE;
		startFlying = 0;

		upArrowWasHolded = false;
		isEntryPipe = false;
		isPrepareEntry = false;

		isEndGame = false;
		isOnPlatform = false;
		//jump_start = -1;
		isPickUp = false;
		coin = 0;

		//isLinkedLeft = false;
		//isLinkedUp = false;
		isLinked = false;

		targetPoint = { 0,0 };
		this->item = nullptr;
		this->movingPlatform = nullptr;
		preNx = nx;
	}

	int GetAniId();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void UpdateWhenEndScene(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void UpdateWhenEntryPipe(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void UpdateWhenPrepareEntry(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void Render();
	void SetState(int state);

	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	BOOLEAN IsPicking() { return isPickUp; }
	int GetNx() { return nx; }

	void SetPickUp(BOOLEAN pick) { isPickUp = pick; }
	void PickingItem(DWORD dt);
	void ReleaseItem(CGameObject* item);
	void UpdateTail(DWORD dt);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel() { return this->level; }

	void DecreaseLevel();
	void SetPowerUP(bool power) { isPowerUp = power; anchor_start = GetTickCount64(); 
								  GameManager::GetInstance()->SetPausedToTransform(true); }
	bool IsPowerUp() { return isPowerUp; }
	//void SetSelfPausing(bool pause) { isSelfPausing = pause; }

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartRecovery() { isRecovering = 1; recovery_start = GetTickCount64(); }
	//for attack
	void SetAttack(bool value);
	bool IsAttack();
	//for flying
	bool IsReachToExpectedSpeed();
	bool IsReadyToFly();
	void SetFlying(bool value) { isFlying = value; flyingTime = FLYING_TIME; }
	bool canSet() { return jumpedTime >= MARIO_MAX_JUMP_TIME; }
	
	//for falling
	bool IsFalling() { return vy > 0 && !isOnPlatform; }
	void SetSlowFalling(bool value) { isSlowFalling = value; slowFallingTime = SLOW_FALLING_TIME; }
	bool IsSlowFalling() { return isSlowFalling; }

	void SetSmallJump();
	bool IsSitting() { return isSitting; }
	
	void SetForEntryPipeDown();
	void SetForEntryPipeUp();
	bool CanEntryPipe() { return canEntryPipe; }
	bool IsPrepareEntry() { return isPrepareEntry; }
	bool IsEntryPipe () { return isEntryPipe; }
	void SetForEndGame(bool value);
	bool UpArrowWasHoled() { return upArrowWasHolded; }
	void SetUpArrow(bool value) { upArrowWasHolded = value; }

	void SetLinked(bool value1, bool value2, DropLift* dropLift);
	//bool IsLinkedLeft() { return isLinkedLeft; }
	//bool IsLinkedUp() { return isLinkedUp; }
	bool IsLinked() { return isLinked; }

	void SetIsStickToPlatform(DropLift* dropLift);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	bool IsUpdateWhenMarioTransform() { return true; }

	bool IsRenderWhenPaused() { return false; }

	int GetDirection() { return this->nx; }
	void SetDirection(int direction) { this->nx = direction; }

	bool IsOnDropLift() { return movingPlatform != nullptr; }
};