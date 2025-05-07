#include "TextMeshPro.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "Game.h"
#include "PlayScene.h"
#include "Mario.h"

void CTextMeshPro::Render()
{
	CMario * mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int level = mario->GetLevel();
	SetText("CURRENT LEVEL " + to_string(level));
	this->id = ID_ANI_TEXT_MESH_PRO;
	//CUserInterface::Render();
	for (auto c : text)
	{
		c->Render();
		DebugOut(L"%d \n", c->characterId);
	}
	DebugOut(L"Was done\n");
}
int CTextMeshPro::HashIDChar(char c)
{
	if (c >= '0' && c <= '9')
		return 28000 + (c - '0') + 1;     // '0' → 28001, '1' → 28002, ..., '9' → 28010
	else if (c >= 'A' && c <= 'Z')
		return 28000 + (c - 'A') + 21;    // 'A' → 28021, 'B' → 28022, ..., 'Z' → 28046
	else
		return -1;
}
void CTextMeshPro::GenerateText()
{
	//DebugOut(L"[INFO] Generate text: %s\n", textString.c_str());
	//for (auto c : text)
	//{
	//	c->Delete();
	//}
	text.clear();
	int modifier = 0;
	CCharacters* character;
	for (int i = 0; i < textString.length(); i++)
	{
		character = new CCharacters(x + i * 10 + modifier, y, HashIDChar(textString[i]));
		text.push_back(character);
		DebugOut(L"%f-%f \n", x + i * 10 + modifier, y);
	}
}



void CCharacters::Render()
{
	this->id = characterId;
	if (id == -1) return;
	CAnimations* animations = CAnimations::GetInstance();
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	animations->Get(id)
		->Render(cx + x + 100, cy + y + 100);
}