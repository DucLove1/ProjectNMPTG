#pragma once
#include "TextMeshPro.h"
#include "debug.h"
#define MAX_LENGTH 3

using namespace std;

class CHUDTimeText : public CTextMeshPro
{

private:

public:
	CHUDTimeText(float x, float y, string str) : CTextMeshPro(x, y, str)
	{
		this->x = x;
		this->y = y;
		this->textString = str;
	}

	void Render() override;
	void FillWithZeroes(string& time);
};


