#include "Portal.h"
#include "Game.h"
#include "Textures.h"
#include "PlayScene.h"
#define TIME_TRANSITION 1000 //ms
CPortal::CPortal(float l, float t, float r, float b, bool isPortalIn, int scene_id )
{
	this->scene_id = scene_id;
	x = l; 
	y = t;
	width = r - l;
	height = b - t;
	time_start = -1;
	fade_transition = nullptr;
	this->isPortalIn = isPortalIn; // true if this portal is for entering the scene, false if it's for exiting
	isTransited = false; // true if the scene start to transition, false otherwise
}

void CPortal::RenderBoundingBox()
{
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

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPortal::SwitchScene()
{
	if(this->time_start == -1)
	{
		this->time_start = GetTickCount64();
		if (isTransited == false)
		{
			float x, y;
			CGame::GetInstance()->GetCamPos(x, y);
			//if (isPortalIn)
			//	fade_transition = new FadeTransition(x, y, 2000, true);
			//else
			fade_transition = new FadeTransition(x,y,this->isPortalIn);
			((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->AddObject(fade_transition);
			isTransited = true; // mark that the scene has started to transition
		}
	}
	if(GetTickCount64() - this->time_start < TIME_TRANSITION)
		return;
	CGame::GetInstance()->InitiateSwitchScene(this->scene_id);
}

void CPortal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->time_start == -1)
		return;
	this->SwitchScene();
}

void CPortal::Render()
{
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - width/2;
	t = y - height/2;
	r = x + width/2;
	b = y + height/2;
}