#include "Pipe.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"
#include "Game.h"

void CPipe::RenderBoundingBox() {
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float yy = y - this->cellHeight / 2 + rect.bottom / 2;

	CGame::GetInstance()->Draw(x - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);

}
void CPipe::Render() {
	if (this->length <= 0) return;

	//for entry pipe
	if ((isEntryPipe && (player->IsEntryPipe() || player->IsPrepareEntry()))
		|| (player != nullptr && player->IsExitPipe()))
	{
		if (player == nullptr)
		{
			this->SetPlayer();
		}
		CAnimations* animations = CAnimations::GetInstance();
			int aniId = -1;

			aniId = player->GetAniId();

			float mx, my;
		player->GetPosition(mx, my);
		animations->Get(aniId)->Render(mx, my);
	}

	//for this
	float yy = y;
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteIdBegin)->Draw(x, yy);
	yy += this->cellHeight;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(this->spriteIdMiddle)->Draw(x, yy);
		yy += this->cellHeight;
	}
	if (length > 1)
		s->Get(this->spriteIdEnd)->Draw(x, yy);
	//RenderBoundingBox();

}
void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth;
	b = t + this->cellHeight * this->length;
}

int CPipe::IsDirectionColliable(float nx, float ny) {
	return 1;
}

void CPipe::SetEntryPipe(bool value)
{
	isEntryPipe = value;
	if (isEntryPipe && player == nullptr)
	{
		this->SetPlayer();
	}
}

void CPipe::SetPlayer()
{
	this->player = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (player == nullptr)
		DebugOut(L"[ERROR] CPipe::SetPlayer - player is nullptr\n");
}