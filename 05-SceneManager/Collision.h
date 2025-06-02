#pragma once

#include <Windows.h>
#include <vector>
#include <algorithm>

using namespace std;

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;

#define COLLISION_TYPE_NORMAL 0
#define COLLISION_TYPE_OVERLAP 1
struct CCollisionEvent
{
	LPGAMEOBJECT src_obj;		// source object : the object from which to calculate collision
	LPGAMEOBJECT obj;			// the target object

	int collision_type;
	float t, nx, ny;

	float dx, dy;				// *RELATIVE* movement distance between this object and obj
	bool isDeleted;

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0,
		LPGAMEOBJECT obj = NULL, LPGAMEOBJECT src_obj = NULL, int collision_type = COLLISION_TYPE_NORMAL)
	{
		this->collision_type = collision_type;
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
		this->src_obj = src_obj;
		this->isDeleted = false;
	}

	int WasCollided();

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
public:
	int GetCollisionType() { return collision_type; }
};

class CCollision
{
	static CCollision* __instance;
public:
	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float& t,
		float& nx,
		float& ny);

	LPCOLLISIONEVENT SweptAABB(
		LPGAMEOBJECT objSrc,
		DWORD dt,
		LPGAMEOBJECT objDest);

	static void Overlap
	(float l1, float t1, float r1, float b1,
		float l2, float t2, float r2, float b2,
		float x1, float x2, float y1, float y2,
		float& t, float& nx, float& ny);

	LPCOLLISIONEVENT Overlap(
		LPGAMEOBJECT objSrc,
		LPGAMEOBJECT objDest,
		bool isInverted = false);

	void Scan(
		LPGAMEOBJECT objSrc,
		DWORD dt,
		vector<LPGAMEOBJECT>* objDests,
		vector<LPCOLLISIONEVENT>& coEvents);

	void Filter(
		LPGAMEOBJECT objSrc,
		vector<LPCOLLISIONEVENT>& coEvents,
		LPCOLLISIONEVENT& colX,
		LPCOLLISIONEVENT& colY,
		int filterBlock,
		int filterX,
		int filterY);

	void Process(LPGAMEOBJECT objSrc, DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	static CCollision* GetInstance();
};