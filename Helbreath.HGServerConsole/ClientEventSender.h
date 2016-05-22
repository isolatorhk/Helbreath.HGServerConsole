#pragma once
#include <windows.h>
#include "net\MessageIndex.h"
#include "char\Client.h"

#define MAXCLIENTS 200

class ClientEventSender
{
public:
	void SendEventToNearClient(CClient **clientList, DWORD dwMsgID, WORD wMsgType, char cMapIndex, short sX, short sY, short sV1, short sV2, short sV3, short sV4);
	ClientEventSender();
	~ClientEventSender();
};

