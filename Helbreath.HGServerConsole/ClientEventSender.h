#pragma once
#include <windows.h>
#include "net\MessageIndex.h"
#include "char\Client.h"
#include "char\ActionID.h"
#include "char\Npc.h"
#include "PlayerHelpers.h"

#define MAXCLIENTS 200
#define GUILDSTARTRANK 12

class ClientEventSender
{
public:
	void SendEventToNearClientB(CClient **clientList, DWORD dwMsgID, WORD wMsgType, char cMapIndex, short sX, short sY, short sV1, short sV2, short sV3, short sV4);
	void SendEventToNearClientA(CClient **clientList, CNpc **npcList, short sOwnerH, char cOwnerType, DWORD dwMsgID, WORD wMsgType, short sV1, short sV2, short sV3);
	void SendNotificationMessage(int iFromH, int iToH, WORD wMsgType, DWORD sV1, DWORD sV2, DWORD sV3, const char * pString,
		DWORD sV4, DWORD sV5, DWORD sV6, DWORD sV7, DWORD sV8, DWORD sV9, char * pString2) const;
	ClientEventSender();
	~ClientEventSender();
	PlayerHelpers *playerHelpers;

	//Temporarly until we introduce json and 
	//once place where you can get those values
	int m_iGameServerMode = 1;
	char *m_cGameServerAddrExternal = "54.171.114.99";
	char *m_cLogServerAddr = "172.31.30.11";
	int  m_iLogServerPort = 321;
};

