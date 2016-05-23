#include "PlayerHelpers.h"

bool PlayerHelpers::IsPlayerHostile(int self, int otherPlayer, CClient **clientList)
{
	CClient *playerA = clientList[self];
	CClient *playerB = clientList[otherPlayer];

	if (playerA == NULL || playerB == NULL) {
		return false;
	}

	if (self == otherPlayer) {
		return true;
	}

	if (playerA->IsNeutral()) {
		if (playerB->m_iPKCount != 0) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (playerA->m_side != playerB->m_side) {
			return true;
		}
		else {
			if (playerB->m_iPKCount != 0) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

PlayerHelpers::PlayerHelpers()
{
}


PlayerHelpers::~PlayerHelpers()
{
}
