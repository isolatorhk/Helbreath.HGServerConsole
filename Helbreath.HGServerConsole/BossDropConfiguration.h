#pragma once

#include "Math.h";

class BossDropConfiguration
{
public:
	int GetAbaddonRareDrop(float fProbA, float fProbB);
	int GetWyvernRareDrop(float fProbA, float fProbB);
	int GetFireWyvernRareDrop(float fProbA, float fProbB);
	int GetThirdRareDrop(float fProbC);
	int GetTigerwormRareDrop();
	int GetHellclawRareDrop();
	BossDropConfiguration();
	~BossDropConfiguration();
};

