#pragma once
#include "UserInterface.h"
#include "AssetIDs.h"
#include "GameManager.h"

class CPieceOfPower :
	public CUserInterface
{
protected:
	bool isCharged;
public:
	CPieceOfPower(float x, float y) : CUserInterface(x, y)
	{
		isCharged = false;
	}
	void Render() override;

	void SetCharged(bool value) { this->isCharged = value; }
	bool ISCharged() { return isCharged; }

};

class CPowerArrow :
	public CPieceOfPower
{
private:
public:
	CPowerArrow(float x, float y) : CPieceOfPower(x, y)
	{
		isCharged = false;
	}
	void Render() override;
};


class CPowerMark :
	public CPieceOfPower
{
private:
public:
	CPowerMark(float x, float y) : CPieceOfPower(x, y)
	{
		isCharged = false;
	}
	void Render() override;
};


class CHUDMarioPower :
	public CUserInterface
{
private:
	vector<CPieceOfPower*> elements;
	void Generate();
public:
	CHUDMarioPower(float x, float y) : CUserInterface(x, y)
	{
		Generate();
	}
	void SetAndCheck();
	void Render() override;
};

