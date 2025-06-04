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
		if (i == 7)
			modify += 12;
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
}
void CHUDMarioPower::Render()
{
	SetAndCheck();
	for (auto e : elements)
	{
		e->Render();
	}
}