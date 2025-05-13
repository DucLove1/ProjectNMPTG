#include "Animation.h"
#include "debug.h"
#include "GameClock.h"
#include "GameObject.h"
#include "Game.h"
#include "PlayScene.h"
#include "CEnemy.h"
#include "VenusBullet.h"
void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	if (sprite == NULL)
		DebugOut(L"[ERROR] Sprite ID %d not found!\n", spriteId);

	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}
bool CAnimation::CheckObjectPause(CGameObject* object)
{
	if (dynamic_cast<CEnemy*>(object) || dynamic_cast<CQuestionBrick*>(object) ||
		dynamic_cast<VenusBullet*>(object) || dynamic_cast<CLeaf*>(object) || dynamic_cast<CMushroom*>(object))
		return true;
	return false;
}
void CAnimation::Render(float x, float y)
{
	CGameObject* curObject = ((LPPLAYSCENE(CGame::GetInstance()->GetCurrentScene())->GetCurObject()));
	bool checkObjectPause = CheckObjectPause(curObject);
	ULONGLONG now = (checkObjectPause) ? GameClock::GetInstance()->GetTime() : GetTickCount64();
	if (dynamic_cast<CMario*>(curObject))
		now = GetTickCount64();
	 if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y);
}

void CAnimation::SetAllFrameTime(DWORD time)
{
	for (int i = 0; i < frames.size(); i++)
	{
		frames[i]->SetTime(time);
	}
}