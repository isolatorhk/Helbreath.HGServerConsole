#include "ClientEventSender.h"

void ClientEventSender::SendEventToNearClientB(CClient **clientList, DWORD dwMsgID, WORD wMsgType, char cMapIndex, short sX, short sY, short sV1, short sV2, short sV3, short sV4)
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

void ClientEventSender::SendEventToNearClientA(CClient **clientList, CNpc **npcList, short sOwnerH, char cOwnerType, DWORD dwMsgID, WORD wMsgType, short sV1, short sV2, short sV3)
{
	int * ip, i, iRet, iShortCutIndex, iStatus, *ipStatus, iDumm, dataLength;
	char  * cp, cKey, data[200];
	DWORD * dwp;
	WORD  * wp;
	short * sp;
	bool    bOwnerSend;
	CClient * pClient;

	ZeroMemory(data, sizeof(data));
	ipStatus = (int *)&iDumm;
	cKey = (char)(rand() % 255) + 1;

	dwp = (DWORD *)(data + INDEX4_MSGID);
	*dwp = dwMsgID;
	wp = (WORD *)(data + INDEX2_MSGTYPE);
	*wp = wMsgType;

	cp = (char *)(data + INDEX2_MSGTYPE + 2);

	if (cOwnerType == OWNERTYPE_PLAYER) {
		pClient = clientList[sOwnerH];
		if (pClient == NULL) return;

		switch (wMsgType) {
		case OBJECTNULLACTION:
		case OBJECTDAMAGE:
		case OBJECTDYING:
			bOwnerSend = TRUE;
			break;
		default:
			bOwnerSend = FALSE;
			break;
		}

		switch (wMsgType)
		{
		case OBJECTMAGIC:
		case OBJECTDAMAGE:
		case OBJECTDAMAGEMOVE:
		case OBJECTDYING:
			dataLength = 11;

			wp = (WORD *)cp;
			*wp = sOwnerH + 30000;
			cp += 2;
			*cp = pClient->m_cDir;
			cp++;
			*cp = (unsigned char)sV1;
			cp++;
			*cp = (unsigned char)sV2;
			cp++;

			if (wMsgType == OBJECTDYING) {
				dataLength = 15;

				sp = (short *)cp;
				*sp = pClient->m_sX;
				cp += 2;
				sp = (short *)cp;
				*sp = pClient->m_sY;
				cp += 2;
			}
			break;

		case OBJECTATTACK:
		case OBJECTATTACKMOVE:
			dataLength = 13;

			wp = (WORD *)cp;
			*wp = sOwnerH + 30000;
			cp += 2;
			*cp = pClient->m_cDir;
			cp++;
			*cp = sV1 - pClient->m_sX;
			cp++;
			*cp = sV2 - pClient->m_sY;
			cp++;
			sp = (short *)cp;
			*sp = sV3;
			cp += 2;
			break;

		case MSGTYPE_CONFIRM:
		case MSGTYPE_REJECT:
		case OBJECTNULLACTION:
		default:
			dataLength = 43;

			wp = (WORD *)cp;
			*wp = sOwnerH;
			cp += 2;
			sp = (short *)cp;
			*sp = pClient->m_sX;
			cp += 2;
			sp = (short *)cp;
			*sp = pClient->m_sY;
			cp += 2;
			sp = (short *)cp;
			*sp = pClient->m_sType;
			cp += 2;
			*cp = pClient->m_cDir;
			cp++;
			memcpy(cp, pClient->m_cCharName, 10);
			cp += 10;
			sp = (short *)cp;
			*sp = pClient->m_sAppr1;
			cp += 2;
			sp = (short *)cp;
			*sp = pClient->m_sAppr2;
			cp += 2;
			sp = (short *)cp;
			*sp = pClient->m_sAppr3;
			cp += 2;
			sp = (short *)cp;
			*sp = pClient->m_sAppr4;
			cp += 2;
			ip = (int *)cp;
			*ip = pClient->m_iApprColor;
			cp += 4;

			ip = (int *)cp;
			ipStatus = ip;
			iStatus = *ip = pClient->m_iStatus;
			cp += 4;

			if (wMsgType != OBJECTNULLACTION || pClient->m_bIsKilled == FALSE) {
				*cp = 0;
			}
			else *cp = 1;
			cp++;
			break;
		}

		iShortCutIndex = 0;


		for (int i = 0; i < MAXCLIENTS; i++)
		{
			CClient *ipClient = clientList[i];
			if (ipClient != NULL && clientList[i]->m_bIsInitComplete) {
				if ((ipClient->m_cMapIndex == pClient->m_cMapIndex) &&
					(ipClient->m_sX >= pClient->m_sX - 11) &&
					(ipClient->m_sX <= pClient->m_sX + 11) &&
					(ipClient->m_sY >= pClient->m_sY - 9) &&
					(ipClient->m_sY <= pClient->m_sY + 9)) {

					if (bOwnerSend == TRUE || i != sOwnerH) {
						if (playerHelpers->IsPlayerHostile(i, sOwnerH, clientList) && sOwnerH != i && clientList[i]->m_iAdminUserLevel == 0) {
							*ipStatus = iStatus & STATUS_ENEMYFLAGS;
						}
						else {
							*ipStatus = iStatus;
						}

						iRet = ipClient->m_pXSock->iSendMsg(data, dataLength, cKey);
					}
				}
			}
		}
	}
	else {
		CNpc * pNpc = npcList[sOwnerH];
		if (pNpc == NULL) return;

		switch (wMsgType)
		{
		case OBJECTDAMAGE:
		case OBJECTDAMAGEMOVE:
		case OBJECTDYING:
			dataLength = 11;

			wp = (WORD *)cp;
			*wp = sOwnerH + 40000;
			cp += 2;
			*cp = pNpc->m_cDir;
			cp++;
			*cp = (unsigned char)sV1;
			cp++;
			*cp = (unsigned char)sV2;
			cp++;

			if (wMsgType == OBJECTDYING) {
				dataLength = 15;

				sp = (short *)cp;
				*sp = pNpc->m_sX;
				cp += 2;
				sp = (short *)cp;
				*sp = pNpc->m_sY;
				cp += 2;
			}
			break;

		case OBJECTATTACK:
		case OBJECTATTACKMOVE:
			dataLength = 13;

			wp = (WORD *)cp;
			*wp = sOwnerH + 40000;
			cp += 2;
			*cp = pNpc->m_cDir;
			cp++;
			*cp = sV1 - pNpc->m_sX;
			cp++;
			*cp = sV2 - pNpc->m_sY;
			cp++;
			sp = (short *)cp;
			*sp = sV3;
			cp += 2;
			break;

		case MSGTYPE_CONFIRM:
		case MSGTYPE_REJECT:
		case OBJECTNULLACTION:
		default:
			dataLength = 27;

			wp = (WORD *)cp;
			*wp = sOwnerH + 10000;
			cp += 2;
			sp = (short *)cp;
			*sp = pNpc->m_sX;
			cp += 2;
			sp = (short *)cp;
			*sp = pNpc->m_sY;
			cp += 2;
			sp = (short *)cp;
			*sp = pNpc->m_sType;
			cp += 2;
			*cp = pNpc->m_cDir;
			cp++;
			memcpy(cp, pNpc->m_cName, 5);
			cp += 5;
			sp = (short *)cp;
			*sp = pNpc->m_sAppr2;
			cp += 2;

			ip = (int *)cp;
			ipStatus = ip;
			*ip = pNpc->m_iStatus;
			cp += 4;
			if (wMsgType != OBJECTNULLACTION || pNpc->m_bIsKilled == FALSE) {
				*cp = 0;
			}
			else *cp = 1;
			cp++;
			break;
		}

		iShortCutIndex = 0;

		CClient * pClient;
		for (int i = 0; i < MAXCLIENTS; i++)
		{
			if ((pClient = clientList[i]) && pClient->m_bIsInitComplete) {
				if ((pClient->m_cMapIndex == pNpc->m_cMapIndex) &&
					(pClient->m_sX >= pNpc->m_sX - 11) &&
					(pClient->m_sX <= pNpc->m_sX + 11) &&
					(pClient->m_sY >= pNpc->m_sY - 9) &&
					(pClient->m_sY <= pNpc->m_sY + 9))
				{
					iRet = pClient->m_pXSock->iSendMsg(data, dataLength, cKey);
				}
			}
		}
	}
}

ClientEventSender::ClientEventSender()
{
	playerHelpers = new PlayerHelpers();
}


ClientEventSender::~ClientEventSender()
{
	delete(playerHelpers);
}
