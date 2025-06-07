#include "HUDCoin.h"
#include "GameManager.h"

#define MAX_LENGTH 1

void CHUDCoin::Render()
{
	//string time = to_string(GameManager::GetInstance()
	//	->GetRemainingTime());
	string coin = to_string(GameManager::GetInstance()
		->GetCoins());

	FillWithZeroes(coin);
	SetText(coin);
	CTextMeshPro::Render();
}

void CHUDCoin::FillWithZeroes(string& coin)
{
	int sz = coin.length();
	if (sz > MAX_LENGTH)
		return;
	while (coin.length() <= MAX_LENGTH)
	{
		coin = "0" + coin;
	}
}
