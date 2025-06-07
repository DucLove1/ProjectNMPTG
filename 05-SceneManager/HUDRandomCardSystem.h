#pragma once
#include "UserInterface.h"
#include "HUDRandomCard.h"
#include <vector>
#define DISTANCE_BETWEEN_CARDS 24
using namespace std;
class HUDRandomCardSystem: public CUserInterface 
{
private:
	vector<HUDRandomCard*> cards; // List of random cards
public:
	HUDRandomCardSystem(float x, float y) : CUserInterface(x, y)
	{
		this->x = x;
		this->y = y;
		for (int i = 0; i < 3; i++)
		{
			HUDRandomCard* card = new HUDRandomCard(x + i * DISTANCE_BETWEEN_CARDS, y, i);
			cards.push_back(card);
		}
	}

	void Render() override;
};

