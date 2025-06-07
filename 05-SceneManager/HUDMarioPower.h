#pragma once
#include "UserInterface.h"
#include "AssetIDs.h"
#include "GameManager.h"
#include "GameClock.h"

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

#define ALERT_TIME 3500

class CHUDMarioPower :
	public CUserInterface
{
private:
	bool preMark;
	bool curMark;
	ULONGLONG startOff;

	vector<CPieceOfPower*> elements;

	void Generate();
public:
	CHUDMarioPower(float x, float y) : CUserInterface(x, y)
	{
		curMark = false;
		preMark = false;
		Generate();
	}
	void SetAndCheck();
	void Render() override;
	void AddedEffect();
};

