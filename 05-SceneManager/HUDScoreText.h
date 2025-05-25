#pragma once
#include "TextMeshPro.h"
#define MAX_LENGTH 6

using namespace std;

class CHUDScoreText : public CTextMeshPro
{
private:

public:
	CHUDScoreText(float x, float y, string str) : CTextMeshPro(x, y, str)
	{
		this->x = x;
		this->y = y;
		this->textString = str;
	}

	void Render() override;
	void FillWithZeroes(string &score);
};

