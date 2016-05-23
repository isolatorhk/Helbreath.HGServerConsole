#pragma once

#include "char\Client.h"

class PlayerHelpers
{
public:
	bool IsPlayerHostile(int self, int otherPlayer, CClient **clientList);
	PlayerHelpers();
	~PlayerHelpers();
};

