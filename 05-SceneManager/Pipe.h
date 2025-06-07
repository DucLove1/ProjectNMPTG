class CMario;
#pragma once
#include "GameObject.h"
#include "Game.h"
#include "PlayScene.h"
#include "Mario.h"

class CPipe : public CGameObject
{
protected:
	int length; //unit cell - length of pipe
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;
	//int spriteIdTop;
	bool isEntryPipe; // true if player is in entry pipe

	int canLetEntry;
	CMario* player; // for entry pipe
	bool MarioOut;


public:
	CPipe(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end, int MarioOut = 0, int canEntry = 0) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;

		this->canLetEntry = canEntry;
		isEntryPipe = false;
		if (MarioOut)
		{
			this->MarioOut = true;
			SetPlayer();
		}
		else
		{
			this->MarioOut = false;
			this->player == nullptr;
		}
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();

	int IsDirectionColliable(float nx, float ny);

	void SetEntryPipe(bool value);

	int GetCanLetEntry() { return canLetEntry; }

	void SetPlayer();
};
typedef CPipe* LPPipe;
