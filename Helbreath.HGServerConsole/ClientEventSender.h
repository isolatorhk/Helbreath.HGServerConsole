#pragma once
#include <windows.h>
#include "net\MessageIndex.h"
#include "char\Client.h"
#include "char\ActionID.h"
#include "char\Npc.h"
#include "PlayerHelpers.h"

#define MAXCLIENTS 200

class ClientEventSender
{
public:
	void SendEventToNearClientB(CClient **clientList, DWORD dwMsgID, WORD wMsgType, char cMapIndex, short sX, short sY, short sV1, short sV2, short sV3, short sV4);
	void SendEventToNearClientA(CClient **clientList, CNpc **npcList, short sOwnerH, char cOwnerType, DWORD dwMsgID, WORD wMsgType, short sV1, short sV2, short sV3);
	ClientEventSender();
	~ClientEventSender();
	PlayerHelpers *playerHelpers;
};

