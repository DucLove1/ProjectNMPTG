#pragma once
#include <vector>
using namespace std;
#define UP1 10000
class ComboScoreSystem
{
private:
	vector<int> scoreList = {100,200,400,800,1000,2000,4000,8000,UP1};
	int index;
	public:
	ComboScoreSystem() {
		index = 0;
	}
	void Reset() { index = 0; }
	void Increase()
	{
		if (index < scoreList.size() - 1)
			index++;
	}
	int GetScore() { return scoreList[index]; }
};

