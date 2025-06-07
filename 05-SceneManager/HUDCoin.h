#pragma once
#include "TextMeshPro.h"
class CHUDCoin : public CTextMeshPro
{
private:
public:
	CHUDCoin(float x, float y, string str) : CTextMeshPro(x, y, str)
	{
		this->x = x;
		this->y = y;
		this->textString = str;
	}

	void Render() override;
	void FillWithZeroes(string& time);
};

