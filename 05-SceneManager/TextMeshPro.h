#pragma once
#include "UserInterface.h"
#include "Game.h"
#include <vector>
#include <string>

#define GAP 8

using namespace std;

class CCharacters : public CUserInterface
{
private:
public:
	int characterId;
	CCharacters(float x, float y, int characterId) : CUserInterface(x, y)
	{
		this->x = x;
		this->y = y;
		this->characterId = characterId;
	}
	void Render() override;
};



class CTextMeshPro : public CUserInterface
{
protected:
	string textString;
	vector <CCharacters*> text;
	float modify;
public:
	CTextMeshPro(float x, float y ,string str) : CUserInterface(x, y)
	{
		float cx, cy;
		CGame::GetInstance()->GetCamPos(cx, cy);
		this->x = cx;
		this->y = cy;

		this->modify = 0;
		this->textString = str;
		GenerateText();
	}
	void Render() override;
	float CalAnchorRight();

	void SetText(string textString);
	void GenerateText();
	int HashIDChar(char c);
};
