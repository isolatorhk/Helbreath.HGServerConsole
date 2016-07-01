#pragma once
#include "Math.h";

class NormalDropConfiguration
{
public:
	int GetAncientStonePiece();
	int WeaponDropByGenerationLevel(int generationLevel);
	int ArmorDropByGenerationLevel(int generationLevel);
	NormalDropConfiguration();
	~NormalDropConfiguration();
};

