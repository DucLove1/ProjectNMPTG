#include "FadeTransition.h"
#include "Textures.h"
#include "Game.h"
#define ID_SPRITE_FADE_TRANSITION 200
void FadeTransition::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isFadingIn)
	{
		alpha += VFADE_TRANSITION * dt;
		if (alpha >= 1.0f) // Finished fading in
		{
			alpha = 1.0f;
			//Delete(); // Remove the transition object after fading in
		}
	}
	else
	{
		alpha -= VFADE_TRANSITION * dt ;
		if (alpha <= 0.0f) // Finished fading out
		{
			alpha = 0.0f;
			Delete(); // Remove the transition object after fading out
		}
	}
}
void FadeTransition::Render()
{
	RenderBoundingBox();
}

void FadeTransition::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - WIDTH / 2;
	t = y - HEIGHT / 2;
	r = x + WIDTH / 2;
	b = y + HEIGHT / 2;
}

void FadeTransition::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_SPRITE_FADE_TRANSITION);
	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, &rect, alpha, rect.right - 1, rect.bottom - 1);
}
