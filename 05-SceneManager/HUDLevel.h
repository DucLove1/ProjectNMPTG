#pragma once
#include "TextMeshPro.h"
class CHUDLevel : public CTextMeshPro
{
private:

public:
	CHUDLevel(float x, float y, string str) : CTextMeshPro(x, y, str)
	{
		this->x = x;
		this->y = y;
		this->textString = str;
	}

	void Render() override;
};

