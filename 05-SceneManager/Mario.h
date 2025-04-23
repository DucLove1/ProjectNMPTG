#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.15f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0002f
#define MARIO_ACCEL_RUN_X	0.0003f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601


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


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_RECOVERY_TIME 2500

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

#pragma endregion

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level;
	int untouchable;

	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	BOOLEAN isPickUp;
	int isRecovering;

	int coin;

	LPGAMEOBJECT item;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdTail();

	int ConvertAniTypeToAniId(int animation_type);
	int GetAniId();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;

		level = MARIO_LEVEL_TAIL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		isPickUp = false;
		coin = 0;

		this->item = nullptr;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
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
	void PickingItem();
	void ReleaseItem(CGameObject* item);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void DecreaseLevel();

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};


