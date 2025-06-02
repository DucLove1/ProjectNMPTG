#pragma once
#include "ComboScoreSystem.h"
class ComboScoreSystemMario : public ComboScoreSystem
{
private:
	static ComboScoreSystemMario* instance;
	ComboScoreSystemMario() : ComboScoreSystem() {}
public:
	static ComboScoreSystemMario* GetInstance()
	{
		if (instance == nullptr)
			instance = new ComboScoreSystemMario();
		return instance;
	}
};
