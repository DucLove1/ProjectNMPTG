#include "UserInterface.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "Game.h"
void CUserInterface::Render()
{
	if (this->id == 0)
		return;
	CAnimations* animations = CAnimations::GetInstance();
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	animations->Get(id)
		->Render(cx + BORDER_POSITION_X + BORDER_WIDTH / 2, cy + BORDER_POSITION_Y + BORDER_HEIGHT / 2);
} 