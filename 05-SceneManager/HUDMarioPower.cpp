#include "HUDMarioPower.h"
#include "Animations.h"
#include "Game.h"
//
// SPLIT BASE CLASS CPieceOfPower
//
void CPieceOfPower::Render()
{
	CUserInterface::Render();
}
//ARROW
void CPowerArrow::Render()
{
	if (ISCharged())
		this->id = ID_ANI_HUD_PIECE_OF_POWER;
	else
		this->id = ID_ANI_HUD_PIECE_OF_POWER_OFF;
	CPieceOfPower::Render();
}
//MARK
void CPowerMark::Render()
{
	if (ISCharged())
		this->id = ID_ANI_HUD_PIECE_OF_POWER_PMARK;
	else
		this->id = ID_ANI_HUD_PIECE_OF_POWER_PMARK_OFF;
	CPieceOfPower::Render();
}

//
// SPLIT CHUDMarioPower
//

void CHUDMarioPower::Generate()
{
	CPieceOfPower* e;
	for (int i = 0; i < 6; i++)
	{
		e = new CPowerArrow(this->x + 9 * i, this->y);
		elements.push_back(e);
	}
	e = new CPowerMark(this->x + 9 * 6 + 12, this->y);
	elements.push_back(e);
}
void CHUDMarioPower::SetAndCheck()
{
	int power = GameManager::GetInstance()->GetPower();
	float modify = 0;
	for (int i = 0; i < 7; i++)
	{
		modify = i * 9;
		if (i == 6)
			modify += 2;
		if (i < power)
		{
			elements[i]->SetCharged(true);
		}
		else
		{
			elements[i]->SetCharged(false);
		}
		elements[i]->SetPosition(this->x + modify, this->y);

	}
	preMark = curMark;
	curMark = elements[6]->ISCharged();
}
void CHUDMarioPower::Render()
{
	SetAndCheck();
	AddedEffect();
	for (auto e : elements)
	{
		e->Render();
	}
}

void CHUDMarioPower::AddedEffect()
{
	ULONGLONG time = GameClock::GetInstance()->GetTime();
	if (preMark == true && preMark != curMark)
	{
		startOff = time;
	}
	bool lightOn = false;
	bool isAlert = false;
	int GAP_TIME = 500;

	if (time - startOff < ALERT_TIME)
	{
		GAP_TIME = 250;
		isAlert = true;
	}

	if (((time - startOff) % GAP_TIME) >= GAP_TIME / 2)
	{
		if (elements[6]->ISCharged() || isAlert)
			lightOn = true;
	}

	elements[6]->SetCharged(lightOn);
}