#include "ClientEventSender.h"

extern class CClient **g_clientList;
extern class CNpc **g_npcList;

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

void ClientEventSender::SendNotificationMessage(int iFromH, int iToH, WORD wMsgType, DWORD sV1, DWORD sV2, DWORD sV3, const char * pString, DWORD sV4, DWORD sV5, DWORD sV6, DWORD sV7, DWORD sV8, DWORD sV9, char * pString2) const
{
	char cData[1000];
	DWORD * dwp;
	WORD  * wp;
	char  * cp;
	short * sp;
	int   * ip, iRet, i;

	if (g_clientList[iToH] == NULL) {
		return;
	}

	ZeroMemory(cData, sizeof(cData));

	dwp = (DWORD *)(cData + INDEX4_MSGID);
	*dwp = MSGID_NOTIFY;
	wp = (WORD *)(cData + INDEX2_MSGTYPE);
	*wp = wMsgType;

	cp = (char *)(cData + INDEX2_MSGTYPE + 2);

	switch (wMsgType) {

	case NOTIFY_HELDENIANVICTORY: //0x0BEB
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 8);
		break;

	case NOTIFY_HELDENIANTELEPORT:
	case NOTIFY_HELDENIANSTART:
	case NOTIFY_HELDENIANEND:
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6);
		break;
	case NOTIFY_HELDENIANCOUNT:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;
		wp = (WORD *)cp;
		*wp = (WORD)sV2;
		cp += 2;
		wp = (WORD *)cp;
		*wp = (WORD)sV3;
		cp += 2;
		wp = (WORD *)cp;
		*wp = (WORD)sV4;
		cp += 2;
		wp = (WORD *)cp;
		*wp = (WORD)sV5;
		cp += 2;
		wp = (WORD *)cp;
		*wp = (WORD)sV6;
		cp += 2;
		wp = (WORD *)cp;
		*wp = (WORD)sV7;
		cp += 2;
		wp = (WORD *)cp;
		*wp = (WORD)sV8;
		cp += 2;
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 22);
		break;

	case NOTIFY_APOCGATECLOSE:
	case NOTIFY_APOCGATEOPEN:
		ip = (int *)cp;
		*ip = sV1;
		cp += 4;
		ip = (int *)cp;
		*ip = sV2;
		cp += 4;
		memcpy(cp, pString, 10);
		cp += 10;
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 24);
		break;

	case NOTIFY_ABADDONKILLED:
		memcpy(cp, g_clientList[iFromH]->m_cCharName, 10);
		cp += 10;
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 16);
		break;

	case NOTIFY_APOCGATESTARTMSG:
	case NOTIFY_APOCGATEENDMSG:
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6);
		break;

	case NOTIFY_LGNPTS:
		dwp = (DWORD*)cp;
		*dwp = sV1;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_RESPONSE_HUNTMODE:
		memcpy(cp, pString, 10);
		cp += 10;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 16);
		break;

	case NOTIFY_REQGUILDNAMEANSWER:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV2;
		cp += 2;

		memcpy(cp, pString, 20);
		cp += 20;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 32);
		break;

	case NOTIFY_TCLOC:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV2;
		cp += 2;

		memcpy(cp, pString, 10);
		cp += 10;

		wp = (WORD *)cp;
		*wp = (WORD)sV4;
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV5;
		cp += 2;

		memcpy(cp, pString2, 10);
		cp += 10;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 34);
		break;

	case NOTIFY_MONSTERCOUNT:
	case NOTIFY_SLATE_STATUS:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 8);
		break;

	case NOTIFY_QUESTCOUNTER:
		ip = (int *)cp;
		*ip = sV1;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 24);
		break;

	case NOTIFY_SLATE_EXP:
	case NOTIFY_SLATE_MANA:
	case NOTIFY_SLATE_INVINCIBLE:
	case NOTIFY_RESURRECTPLAYER:
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6);
		break;

	case NOTIFY_SLATE_CREATEFAIL:
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6);
		break;

	case NOTIFY_SLATE_CREATESUCCESS:
		dwp = (DWORD *)cp;
		*dwp = sV1;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_PARTY:
		switch (sV1) {
		case 4:
		case 6:
			wp = (WORD *)cp;
			*wp = (WORD)sV1;
			cp += 2;
			wp = (WORD *)cp;
			*wp = (WORD)sV2;
			cp += 2;
			wp = (WORD *)cp;
			*wp = (WORD)sV3;
			cp += 2;
			memcpy(cp, pString, 10);
			cp += 10;
			iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 12 + 10);
			break;

		case 5:
			wp = (WORD *)cp;
			*wp = (WORD)sV1;
			cp += 2;
			wp = (WORD *)cp;
			*wp = (WORD)sV2;
			cp += 2;
			wp = (WORD *)cp;
			*wp = (WORD)sV3;
			cp += 2;
			memcpy(cp, pString, sV3 * 11);
			cp += sV3 * 11;
			iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 12 + sV3 * 11);
			break;

		default:
			wp = (WORD *)cp;
			*wp = (WORD)sV1;
			cp += 2;
			wp = (WORD *)cp;
			*wp = (WORD)sV2;
			cp += 2;
			wp = (WORD *)cp;
			*wp = (WORD)sV3;
			cp += 2;
			wp = (WORD *)cp;
			*wp = (WORD)sV4;
			cp += 2;
			iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 14);
			break;
		}
		break;

	case NOTIFY_PARTY_COORDS:
		memcpy(cp, pString, 10);
		cp += 10;
		sp = (short *)cp;
		*sp = sV1;
		cp += 2;
		sp = (short *)cp;
		*sp = sV2;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 20);
		break;

	case NOTIFY_GRANDMAGICRESULT:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV2;
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV3;
		cp += 2;

		memcpy(cp, pString, 10);
		cp += 10;

		wp = (WORD *)cp;
		*wp = (WORD)sV4;
		cp += 2;

		//		sp = (short *)cp;
		//		*sp = (short)sV9;
		//		cp += 2;

		if (sV9 > 0) {
			memcpy(cp, pString2, (sV9 + 1) * 2);
			cp += (sV9 + 1) * 2;
		}
		else
		{
			sp = (short *)cp;
			*sp = (short)0;
			cp += 2;
		}

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 24 + (sV9 + 1) * 2);
		break;

	case NOTIFY_MAPSTATUSNEXT:
		memcpy(cp, pString, sV1);
		cp += sV1;
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6 + sV1);
		break;

	case NOTIFY_MAPSTATUSLAST:
		memcpy(cp, pString, sV1);
		cp += sV1;
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6 + sV1);
		break;

	case NOTIFY_LOCKEDMAP:
		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;

		memcpy(cp, pString, 10);
		cp += 10;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 18);
		break;

	case NOTIFY_BUILDITEMSUCCESS:
	case NOTIFY_BUILDITEMFAIL:
		if (sV1 >= 0) {
			sp = (short *)cp;
			*sp = (short)sV1;
			cp += 2;
		}
		else {
			sp = (short *)cp;
			*sp = (short)sV1 + 10000;
			cp += 2;
		}

		sp = (short *)cp;
		*sp = (short)sV2;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_HELP:
	case NOTIFY_QUESTREWARD:
		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV2;
		cp += 2;

		ip = (int *)cp;
		*ip = (int)sV3;
		cp += 4;

		memcpy(cp, pString, 20);
		cp += 20;

		ip = (int *)cp;
		*ip = (int)sV4;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 38);
		break;

	case NOTIFY_CANNOTCONSTRUCT:
	case NOTIFY_METEORSTRIKECOMING:
	case NOTIFY_METEORSTRIKEHIT:
	case NOTIFY_HELPFAILED:
	case NOTIFY_SPECIALABILITYENABLED:
	case NOTIFY_FORCEDISCONN:
	case NOTIFY_OBSERVERMODE:
	case NOTIFY_QUESTCOMPLETED:
	case NOTIFY_QUESTABORTED:
		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 8);
		break;

	case NOTIFY_QUESTCONTENTS:
		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV2;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV3;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV4;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV5;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV6;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV7;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV8;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV9;
		cp += 2;

		if (pString2 != NULL) memcpy(cp, pString2, 20);
		cp += 20;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 44);
		break;

	case NOTIFY_GIZONITEMUPGRADELEFT:
	case NOTIFY_ITEMATTRIBUTECHANGE:

		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;

		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV2;
		cp += 4;

		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV3;
		cp += 4;

		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV4;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 20);
		break;

	case NOTIFY_ITEMUPGRADEFAIL:

		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 8);

		break;

	case NOTIFY_GIZONEITEMCHANGE:
		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;

		*cp = (char)sV2;
		cp++;

		sp = (short *)cp;
		*sp = (short)sV3;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV4;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV5;
		cp += 2;

		*cp = (char)sV6;
		cp++;

		*cp = (char)sV7;
		cp++;


		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV8;
		cp += 4;

		memcpy(cp, pString, 20);
		cp += 20;


		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 41);
		break;

	case NOTIFY_ENERGYSPHERECREATED:
	case NOTIFY_ITEMCOLORCHANGE:
		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV2;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_NOMOREAGRICULTURE:
	case NOTIFY_AGRICULTURESKILLLIMIT:
	case NOTIFY_AGRICULTURENOAREA:
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6);
		break;

	case NOTIFY_NOMORECRUSADESTRUCTURE:
	case NOTIFY_EXCHANGEITEMCOMPLETE:
	case NOTIFY_CANCELEXCHANGEITEM:
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6);
		break;

	case NOTIFY_SETEXCHANGEITEM:
		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV2;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV3;
		cp += 2;

		ip = (int *)cp;
		*ip = (int)sV4;
		cp += 4;

		*cp = (char)sV5;
		cp++;

		sp = (short *)cp;
		*sp = (short)sV6;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV7;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV8;
		cp += 2;

		memcpy(cp, pString, 20);
		cp += 20;

		memcpy(cp, g_clientList[iFromH]->m_cCharName, 10);
		cp += 10;


		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV9;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 57);
		break;

	case NOTIFY_OPENEXCHANGEWINDOW:
		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV2;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV3;
		cp += 2;

		ip = (int *)cp;
		*ip = (int)sV4;
		cp += 4;

		*cp = (char)sV5;
		cp++;

		sp = (short *)cp;
		*sp = (short)sV6;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV7;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV8;
		cp += 2;

		memcpy(cp, pString, 20);
		cp += 20;

		memcpy(cp, g_clientList[iFromH]->m_cCharName, 10);
		cp += 10;


		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV9;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 57);
		break;

	case NOTIFY_NOTFLAGSPOT:
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6);
		break;

	case NOTIFY_ITEMPOSLIST:
		for (i = 0; i < MAXITEMS; i++) {
			sp = (short *)cp;
			*sp = g_clientList[iToH]->m_ItemPosList[i].x;
			cp += 2;
			sp = (short *)cp;
			*sp = g_clientList[iToH]->m_ItemPosList[i].y;
			cp += 2;
		}
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6 + MAXITEMS * 4);
		break;

	case NOTIFY_ENEMYKILLS:
		ip = (int *)cp;
		*ip = (int)sV1;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_CRUSADE:
		ip = (int *)cp;
		*ip = (int)sV1;
		cp += 4;

		ip = (int *)cp;
		*ip = (int)sV2;
		cp += 4;

		ip = (int *)cp;
		*ip = (int)sV3;
		cp += 4;

		ip = (int *)cp;
		*ip = (int)sV4;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 22);
		break;

	case NOTIFY_CONSTRUCTIONPOINT:
	case NOTIFY_SPECIALABILITYSTATUS:
	case NOTIFY_DAMAGEMOVE:
		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV2;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV3;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 12);
		break;

	case NOTIFY_DOWNSKILLINDEXSET:
	case NOTIFY_RESPONSE_CREATENEWPARTY:
		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 8);
		break;

	case NOTIFY_ADMINIFO:
		switch (sV1) {
		case 1:

			ip = (int *)cp;
			*ip = g_npcList[sV2]->m_iHP;
			cp += 4;

			ip = (int *)cp;
			*ip = g_npcList[sV2]->m_iDefenseRatio;
			cp += 4;

			ip = (int *)cp;
			*ip = g_npcList[sV2]->m_bIsSummoned;
			cp += 4;

			ip = (int *)cp;
			*ip = g_npcList[sV2]->m_cActionLimit;
			cp += 4;

			ip = (int *)cp;
			*ip = g_npcList[sV2]->m_iHitDice;
			cp += 4;

			dwp = (DWORD *)cp;
			*dwp = g_npcList[sV2]->m_dwDeadTime;
			cp += 4;

			dwp = (DWORD *)cp;
			*dwp = g_npcList[sV2]->m_dwRegenTime;
			cp += 4;

			ip = (int *)cp;
			*ip = (int)g_npcList[sV2]->m_bIsKilled;
			cp += 4;

			iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 26 + 12);
			break;
		}
		break;

	case NOTIFY_NPCTALK:
		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV2;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV3;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV4;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV5;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV6;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV7;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV8;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV9;
		cp += 2;

		if (pString != NULL) memcpy(cp, pString, 20);
		cp += 20;

		if (pString2 != NULL) memcpy(cp, pString2, 20);
		cp += 20;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 64);
		break;
	case NOTIFY_EVENTILLUSION:
	case NOTIFY_EVENTTP:
		*cp = (char)sV1;
		cp++;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 7);
		break;

	case NOTIFY_EVENTSPELL:
		*cp = sV1;
		cp++;
		*cp = sV2;
		cp++;
		*cp = g_clientList[iToH]->IsGM();
		cp++;
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 9);
		break;

	case NOTIFY_EVENTARMOR:
	case NOTIFY_EVENTSHIELD:
	case NOTIFY_EVENTCHAT:
	case NOTIFY_EVENTPARTY:
		*cp = sV1;
		cp++;
		*cp = g_clientList[iToH]->IsGM();
		cp++;
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 8);
		break;

	case NOTIFY_EVENTRESET:
	case NOTIFY_CRAFTING_SUCCESS:
	case NOTIFY_PORTIONSUCCESS:
	case NOTIFY_LOWPORTIONSKILL:
	case NOTIFY_PORTIONFAIL:
	case NOTIFY_NOMATCHINGPORTION:
	case NOTIFY_CRAFTING_FAIL:
	case NOTIFY_NOMATCHINGCRAFTING:
	case NOTIFY_NO_CRAFT_CONTRIB:
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6);
		break;

	case NOTIFY_SUPERATTACKLEFT:
		sp = (short *)cp;
		*sp = g_clientList[iToH]->m_iSuperAttackLeft;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 8);
		break;

	case NOTIFY_SAFEATTACKMODE:
		*cp = g_clientList[iToH]->m_bIsSafeAttackMode;
		cp++;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 7);
		break;

	case NOTIFY_QUERY_JOINPARTY:
	case NOTIFY_IPACCOUNTINFO:
		strcpy(cp, pString);
		cp += strlen(pString);

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6 + strlen(pString) + 1);
		break;

	case NOTIFY_REWARDGOLD:
		dwp = (DWORD *)cp;
		*dwp = g_clientList[iToH]->m_iRewardGold;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_SERVERSHUTDOWN:
		*cp = (char)sV1;
		cp++;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 7);
		break;

	case NOTIFY_GLOBALATTACKMODE:
	case NOTIFY_WHETHERCHANGE:
		*cp = (char)sV1;
		cp++;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 7);
		break;

	case NOTIFY_MONSTEREVENT_POSITION:
		*cp = (char)sV3;
		cp++;

		sp = (short*)cp;
		*sp = (short)sV1;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV2;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 11);
		break;


	case NOTIFY_FISHCANCELED:
	case NOTIFY_FISHSUCCESS:
	case NOTIFY_FISHFAIL:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 8);
		break;

	case NOTIFY_DEBUGMSG:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 8);
		break;

	case NOTIFY_FISHCHANCE:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 8);
		break;

	case NOTIFY_ENERGYSPHEREGOALIN:
	case NOTIFY_EVENTFISHMODE:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV2;
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV3;
		cp += 2;

		memcpy(cp, pString, 20);
		cp += 20;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 32);
		break;

	case NOTIFY_NOTICEMSG:
		memcpy(cp, pString, strlen(pString));
		cp += strlen(pString);

		*cp = NULL;
		cp++;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, strlen(pString) + 7);
		break;

	case NOTIFY_CANNOTRATING:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 8);
		break;

	case NOTIFY_RATINGPLAYER:
		*cp = (char)sV1;
		cp++;

		memcpy(cp, pString, 10);
		cp += 10;

		ip = (int *)cp;
		*ip = g_clientList[iToH]->m_reputation;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 22);
		break;

	case NOTIFY_ADMINUSERLEVELLOW:
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6);
		break;

	case NOTIFY_PLAYERSHUTUP:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		memcpy(cp, pString, 10);
		cp += 10;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 19);
		break;

	case NOTIFY_TIMECHANGE:
		*cp = (char)sV1;
		cp++;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 7);
		break;

	case NOTIFY_TOBERECALLED:
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6);
		break;

	case NOTIFY_HUNGER:
		*cp = (char)sV1;
		cp++;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 7);
		break;

	case NOTIFY_PLAYERPROFILE:
		if (strlen(pString) > 100) {
			memcpy(cp, pString, 100);
			cp += 100;
		}
		else {
			memcpy(cp, pString, strlen(pString));
			cp += strlen(pString);
		}
		*cp = NULL;
		cp++;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 7 + strlen(pString));
		break;

	case NOTIFY_PLAYERONGAME:
	case NOTIFY_FRIENDONGAME:
		memcpy(cp, pString, 10);
		cp += 10;
		if (pString != NULL) {
			memcpy(cp, pString2, 14);
			cp += 14;
		}
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 31);
		break;

	case NOTIFY_WHISPERMODEON:
	case NOTIFY_WHISPERMODEOFF:
	case NOTIFY_PLAYERNOTONGAME:
		memcpy(cp, pString, 10);
		cp += 10;
		memcpy(cp, "             ", 10);
		cp += 10;
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 27);
		break;

	case NOTIFY_ITEMSOLD:
	case NOTIFY_ITEMREPAIRED:
		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV1;
		cp += 4;
		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV2;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 14);
		break;

	case NOTIFY_REPAIRITEMPRICE:
	case NOTIFY_SELLITEMPRICE:
		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV1;
		cp += 4;
		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV2;
		cp += 4;
		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV3;
		cp += 4;
		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV4;
		cp += 4;

		memcpy(cp, pString, 20);
		cp += 20;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 42);
		break;

	case NOTIFY_CANNOTREPAIRITEM:
	case NOTIFY_CANNOTSELLITEM:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV2;
		cp += 2;

		memcpy(cp, pString, 20);
		cp += 20;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 30);

		break;

		//(word)sV1, sV2
	case NOTIFY_SHOWMAP:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV2;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

		//(word)sV1
	case NOTIFY_SKILLUSINGEND:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 8);
		break;

	case NOTIFY_TOTALUSERS:
		wp = (WORD *)cp;
		*wp = (WORD)(sV1);
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 8);
		break;

		// (char)sV1
	case NOTIFY_CTRWINNER:
	case NOTIFY_EVENTSTART:
	case NOTIFY_EVENTSTARTING:
	case NOTIFY_EVENTSTARTING2:
	case NOTIFY_EVENTSTARTING3:
	case NOTIFY_RELICINALTAR:
		*cp = (char)sV1;
		cp++;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 7);
		break;

	case NOTIFY_CASUALTIES:
		wp = (WORD *)cp;
		*wp = (WORD)sV1; // Aresden deaths
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV2; // Elvine
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV3; // Istria
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV4; // Aresden kills
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV5; // Elvine
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV6; // Istria
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 18);
		break;

	case NOTIFY_RELICPOSITION:
		wp = (WORD *)cp;
		*wp = (WORD)sV1; //Relic X
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV2; //Relic Y
		cp += 2;
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_RELICGRABBED:
		memcpy(cp, pString, 10);
		cp += 10;
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 17);
		break;

	case NOTIFY_MAGICEFFECTOFF:
	case NOTIFY_MAGICEFFECTON:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV2;
		cp += 4;

		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV3;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 16);
		break;

	case NOTIFY_CANNOTITEMTOBANK:
	case NOTIFY_SETTING_FAILED:
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6);
		break;

	case NOTIFY_SERVERCHANGE:
		memcpy(cp, g_clientList[iToH]->m_cMapName, 10);
		cp += 10;

		if (m_iGameServerMode == 1) { // LAN
			memcpy(cp, m_cGameServerAddrExternal, 15);
		}
		else { // INTERNET
			memcpy(cp, m_cLogServerAddr, 15);
		}
		cp += 15;

		ip = (int *)cp;
		*ip = m_iLogServerPort;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 16 + 19);
		break;

	case NOTIFY_SKILL:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV2;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_SETITEMCOUNT:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV2;
		cp += 4;

		*cp = (char)sV3;
		cp++;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 13);
		break;

	case NOTIFY_ITEMDEPLETED_ERASEITEM:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV2;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_DROPITEMFIN_COUNTCHANGED:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		ip = (int *)cp;
		*ip = (int)sV2;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 12);
		break;

	case NOTIFY_DROPITEMFIN_ERASEITEM:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		ip = (int *)cp;
		*ip = (int)sV2;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 12);
		break;

	case NOTIFY_CANNOTGIVEITEM:
	case NOTIFY_GIVEITEMFIN_COUNTCHANGED:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		ip = (int *)cp;
		*ip = (int)sV2;
		cp += 4;

		memcpy(cp, pString, 20);
		cp += 20;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 32);
		break;

	case NOTIFY_GIVEITEMFIN_ERASEITEM:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		ip = (int *)cp;
		*ip = (int)sV2;
		cp += 4;

		memcpy(cp, pString, 20);
		cp += 20;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 32);
		break;

	case NOTIFY_ENEMYKILLREWARD:
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->m_iExp;
		cp += 4;
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->m_iEnemyKillCount;
		cp += 4;
		memcpy(cp, g_clientList[sV1]->m_cCharName, 10);
		cp += 10;
		memcpy(cp, g_clientList[sV1]->m_cGuildName, 20);
		cp += 20;
		sp = (short *)cp;
		*sp = (short)g_clientList[sV1]->m_iGuildRank;
		cp += 2;
		sp = (short *)cp;
		*sp = (short)g_clientList[iToH]->m_iWarContribution;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 48);
		break;

	case NOTIFY_PKCAPTURED:

		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;
		wp = (WORD *)cp;
		*wp = (WORD)sV2;
		cp += 2;
		memcpy(cp, pString, 10);
		cp += 10;
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->m_iRewardGold;
		cp += 4;
		dwp = (DWORD *)cp;
		*dwp = g_clientList[iToH]->m_iExp;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 28);
		break;

	case NOTIFY_PKPENALTY:

		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->m_iExp;
		cp += 4;
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->GetStr();
		cp += 4;
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->GetVit();
		cp += 4;
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->GetDex();
		cp += 4;
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->GetInt();
		cp += 4;
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->GetMag();
		cp += 4;
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->m_iCharisma;
		cp += 4;
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->m_iPKCount;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 38);
		break;

	case NOTIFY_TRAVELERLIMITEDLEVEL:
	case NOTIFY_LIMITEDLEVEL:

		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->m_iExp;
		cp += 4;
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_ITEMRELEASED:
	case NOTIFY_ITEMLIFESPANEND:
		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;
		sp = (short *)cp;
		*sp = (short)sV2;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_KILLED:

		memcpy(cp, pString, 20);
		cp += 20;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 26);
		break;

	case NOTIFY_EXP:
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->m_iExp;
		cp += 4;

		ip = (int *)cp;
		*ip = g_clientList[iToH]->m_reputation;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 14);
		break;

	case NOTIFY_HP:
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->m_iHP;
		cp += 4;
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->m_iMP;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 14);
		break;

	case NOTIFY_MP:
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->m_iMP;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_SP:
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->m_iSP;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_CHARISMA:
		dwp = (DWORD *)cp;
		*dwp = (DWORD)g_clientList[iToH]->m_iCharisma;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_SETTING_SUCCESS:
	case NOTIFY_LEVELUP:
		ip = (int *)cp;
		*ip = g_clientList[iToH]->m_iLevel;
		cp += 4;

		ip = (int *)cp;
		*ip = g_clientList[iToH]->GetStr();
		cp += 4;

		ip = (int *)cp;
		*ip = g_clientList[iToH]->GetVit();
		cp += 4;

		ip = (int *)cp;
		*ip = g_clientList[iToH]->GetDex();
		cp += 4;

		ip = (int *)cp;
		*ip = g_clientList[iToH]->GetInt();
		cp += 4;

		ip = (int *)cp;
		*ip = g_clientList[iToH]->GetMag();
		cp += 4;

		ip = (int *)cp;
		*ip = g_clientList[iToH]->m_iCharisma;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 34);
		break;

	case NOTIFY_QUERY_DISMISSGUILDREQPERMISSION:
	case NOTIFY_QUERY_JOINGUILDREQPERMISSION:
	case NOTIFY_CANNOTJOINMOREGUILDSMAN:

		memcpy(cp, g_clientList[iFromH]->m_cCharName, 10);
		cp += 10;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 16);
		break;

	case COMMONTYPE_JOINGUILDAPPROVE:
		if (g_clientList[iFromH] != NULL)
			memcpy(cp, g_clientList[iFromH]->m_cGuildName, 20);
		else memcpy(cp, "?", 1);
		cp += 20;

		sp = (short *)cp;
		*sp = GUILDSTARTRANK;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 28);
		break;

	case COMMONTYPE_JOINGUILDREJECT:
	case COMMONTYPE_DISMISSGUILDAPPROVE:
	case COMMONTYPE_DISMISSGUILDREJECT:
		if (g_clientList[iFromH] != NULL)
			memcpy(cp, g_clientList[iFromH]->m_cGuildName, 20);
		else memcpy(cp, "?", 1);
		cp += 20;

		sp = (short *)cp;
		*sp = GUILDSTARTRANK;
		cp += 2;

		memcpy(cp, g_clientList[iToH]->m_cLocation, 10);
		cp += 10;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 38);
		break;

	case NOTIFY_GUILDDISBANDED:

		memcpy(cp, pString, 20);
		cp += 20;

		memcpy(cp, g_clientList[iToH]->m_cLocation, 10);
		cp += 10;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 36);
		break;

	case NOTIFY_FIGHTZONERESERVE:
		ip = (int *)cp;
		*ip = (int)sV1;
		cp += 4;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_NOGUILDMASTERLEVEL:
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6);
		break;

	case NOTIFY_CANNOTBANGUILDMAN:
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6);
		break;

	case NOTIFY_CANNOTRECALL:
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6);
		break;

	case NOTIFY_FORCERECALLTIME:
		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 8);
		break;

	case NOTIFY_TELEPORT_REJECTED:
		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;
		sp = (short *)cp;
		*sp = (short)sV2;
		cp += 2;
		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case NOTIFY_SPELL_SKILL:
		for (i = 0; i < MAXMAGICTYPE; i++) {
			*cp = g_clientList[iToH]->m_cMagicMastery[i];
			cp++;
		}

		for (i = 0; i < MAXSKILLTYPE; i++) {
			*cp = g_clientList[iToH]->m_cSkillMastery[i];
			cp++;
		}

		iRet = g_clientList[iToH]->m_pXSock->iSendMsg(cData, 6 + MAXMAGICTYPE + MAXSKILLTYPE);
		break;
	}

	switch (iRet) {
	case XSOCKEVENT_QUENEFULL:
	case XSOCKEVENT_SOCKETERROR:
	case XSOCKEVENT_CRITICALERROR:
	case XSOCKEVENT_SOCKETCLOSED:

		//DeleteClient(iToH, TRUE, TRUE);
		return;
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
