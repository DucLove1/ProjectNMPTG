#pragma once
#include "TextMeshPro.h"

using namespace std;

class CHUDLifeText : public CTextMeshPro
{
private:

public:
	CHUDLifeText(float x, float y, string str) : CTextMeshPro(x, y, str)
	{
		this->x = x;
		this->y = y;
		this->textString = str;
	}

	void Render() override;

};

