#pragma once
#include "Koopa.h"
#include "AssetIDs.h"
#define KOOPA_JUMP_FORCE 0.3f
//#define TIME_OUT_OF_SHELL 5000

class GreenKoopa : public Koopa
{
	//ULONGLONG timeStartInShell;
public:
	GreenKoopa(float x, float y, int state) : Koopa(x, y, GREEN_KOOPA, state)
	{
		this->vx = -0.05f;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void UpdateStateHasWing();
	void UpdateStateHasNoWing();
};


