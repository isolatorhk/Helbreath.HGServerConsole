#include "ClientEventSender.h"

void ClientEventSender::SendEventToNearClient(CClient **clientList, DWORD dwMsgID, WORD wMsgType, char cMapIndex, short sX, short sY, short sV1, short sV2, short sV3, short sV4)
{
	int i, iRet, iShortCutIndex;
	char  * cp, cData[100];
	DWORD * dwp, dwTime;
	WORD * wp;
	short * sp;	
	char  cKey;

	cKey = (char)(rand() % 255) + 1;

	ZeroMemory(cData, sizeof(cData));

	dwp = (DWORD *)(cData + INDEX4_MSGID);
	*dwp = dwMsgID;
	wp = (WORD *)(cData + INDEX2_MSGTYPE);
	*wp = wMsgType;

	cp = (char *)(cData + INDEX2_MSGTYPE + 2);

	sp = (short *)cp;
	*sp = sX;
	cp += 2;

	sp = (short *)cp;
	*sp = sY;
	cp += 2;

	sp = (short *)cp;
	*sp = sV1;
	cp += 2;

	sp = (short *)cp;
	*sp = sV2;
	cp += 2;

	sp = (short *)cp;
	*sp = sV3;
	cp += 2;

	sp = (short *)cp;
	*sp = sV4;
	cp += 2;

	dwTime = timeGetTime();
	
	iShortCutIndex = 0;
	
	for (int i = 0; i < MAXCLIENTS; i++)
	{
		CClient *pClient = clientList[i];
		if (pClient != NULL) {
			if ((pClient->m_cMapIndex == cMapIndex) &&
				(pClient->m_sX >= sX - 10) &&
				(pClient->m_sX <= sX + 10) &&
				(pClient->m_sY >= sY - 8) &&
				(pClient->m_sY <= sY + 8)) {
				iRet = clientList[i]->m_pXSock->iSendMsg(cData, 18, cKey);
			}
		}
	}	
}

ClientEventSender::ClientEventSender()
{
}


ClientEventSender::~ClientEventSender()
{
}
