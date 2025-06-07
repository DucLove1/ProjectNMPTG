#include "HUDRandomCardSystem.h"

void HUDRandomCardSystem::Render()
{
	for(auto& card : cards) 
	{
		if (card != nullptr) 
		{
			card->Render();
		}
	}
}
