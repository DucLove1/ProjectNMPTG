#pragma once
#include "UserInterface.h"
#include "Game.h"
#include <vector>
#include <string>

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
private:
	string textString;
	vector <CCharacters*> text;
public:
	CTextMeshPro(float x, float y, string str) : CUserInterface(x, y)
	{
		float cx, cy;
		CGame::GetInstance()->GetCamPos(cx, cy);
		this->x = cx;
		this->y = cy;

		this->textString = str;
		GenerateText();
	}
	void Render() override;
	void SetText(string textString)
	{
		this->textString = textString;
		GenerateText();
	}
	void GenerateText();
	int HashIDChar(char c);
};
