#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <winbase.h>
#include <mmsystem.h>
#include <time.h>		   
#include "winmain.h"
#include "..\HG.h"
#include "..\net\UserMessages.h"
#include "..\GlobalDef.h"
#include "..\res\Resource.h"

// --------------------------------------------------------------

#define WM_USER_TIMERSIGNAL		WM_USER + 500

// Listbox
static HWND    List1;
static HWND    Edit1;
static HWND    Button1;
static HWND    Button2;
static HWND    Button3;
static HINSTANCE BCX_hInstance;
static int     BCX_ScaleX;
static int     BCX_ScaleY;
static char    BCX_ClassName[2048];
int ItemCount=0;
bool scrolling = true;


char			szAppClass[32];
HWND			G_hWnd = NULL;
char			G_cMsgList[120*50];
bool            G_cMsgUpdated =	FALSE;
char            g_cTxt[512];
char            g_msg[50];
char			G_cData50000[50000];
MMRESULT        G_mmTimer = NULL;

char			G_cLogBuffer[30000] ;
short			G_sLogCounter ;
DWORD			G_dwLogTime ; 


class XSocket * G_pListenSock = NULL;
class XSocket * G_pLogSock    = NULL;
class CGame *   g_game       = NULL;

class CMap	**	g_mapList	= NULL;
class CClient ** g_clientList = NULL;
class CNpc **	g_npcList = NULL;
class CNpc **   g_npcConfigList = NULL;
class CMagic ** g_magicConfigList = NULL;

int * g_skillSSNpoint = NULL;

int             G_iQuitProgramCount = 0;
bool            G_bShutdown = FALSE; 

RECT            rctSrvList;

//=============================================================================
struct sMsg
{
        char Message[MAXLOGMSGS][MAXLOGMSGSIZE];
        BYTE MsgLvl[MAXLOGMSGS];
        WORD CurMsg;
}LogMsg;
//=============================================================================
void Initialize()
{

	if (_InitWinsock() == FALSE) {
		MessageBox(G_hWnd, "Socket 1.1 not found! Cannot execute program.","ERROR", MB_ICONEXCLAMATION | MB_OK);
		PostQuitMessage(0);
		return;
	}

	g_game = new class CGame(G_hWnd);
	if (g_game->bInit() == FALSE) {
		PutLogList("(!!!) STOPPED!");
		return;
	}

	SetPriorityClass( GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS );

	//G_mmTimer = _StartTimer(TICKDELAY);

	G_pListenSock = new class XSocket(G_hWnd, SERVERSOCKETBLOCKLIMIT);
	G_pListenSock->bListen(g_game->m_cGameServerAddr, g_game->m_iGameServerPort, WM_USER_ACCEPT);


	G_sLogCounter = 0 ;
	ZeroMemory(G_cLogBuffer, sizeof(G_cLogBuffer));
}
//=============================================================================
void OnDestroy()
{
	if (G_pListenSock != NULL) delete G_pListenSock;
	if (G_pLogSock != NULL) delete G_pLogSock;

	if (g_game != NULL) {
		g_game->Quit();
		delete g_game;
	}

	if (G_mmTimer != NULL) _StopTimer(G_mmTimer);
	_TermWinsock();

	PostQuitMessage(0);
}
//=============================================================================
void UpdateScreen()
{
	if (G_cMsgUpdated == TRUE) {
		InvalidateRect(G_hWnd, NULL, TRUE);
		G_cMsgUpdated = FALSE;
	}
}
//=============================================================================
void OnPaint()
{
 HDC hdc;
 PAINTSTRUCT ps;
 register short i;
 char CurMsg;

	hdc = BeginPaint(G_hWnd, &ps);

        FillRect(hdc, &rctSrvList, (HBRUSH)(7));
        SelectObject(hdc, GetStockObject(ANSI_VAR_FONT));
	SetBkMode(hdc,TRANSPARENT);

	CurMsg = LogMsg.CurMsg;
        for (i = 0; i <= MAXLOGSTOSHOW; i++)
            {
             if(CurMsg < 0) CurMsg = (MAXLOGMSGS-1);
	     if (strlen(LogMsg.Message[CurMsg]) != NULL)
                {
                 switch(LogMsg.MsgLvl[CurMsg]){
                   case WARN_MSG:
                   SetTextColor(hdc, clMaroon);
                   break;

                   case INFO_MSG:
                   SetTextColor(hdc, clNavy);
                   break;
				   
				   default:
                   SetTextColor(hdc, clBlack);
                   break;
                 }
                 TextOut(hdc, 5, (MAXLOGSTOSHOW*14)-(i*14)+4, LogMsg.Message[CurMsg], strlen(LogMsg.Message[CurMsg]));
                }
             CurMsg --;
            }

	if (g_game	!= NULL)
		g_game->DisplayInfo(hdc);

	EndPaint(G_hWnd, &ps);
}
//=============================================================================
void _StopTimer(MMRESULT timerid)
{
 TIMECAPS caps;

	if (timerid != 0) {
		timeKillEvent(timerid);
		timerid = 0;
		timeGetDevCaps(&caps, sizeof(caps));
		timeEndPeriod(caps.wPeriodMin);
	}
}
//=============================================================================
void PutLogFileList(const char * cStr, char *FileName)
{
 FILE * pFile;
 char cBuffer[MAXLOGLINESIZE+100];
 SYSTEMTIME SysTime;

        _mkdir("Logs");
		if(strlen(cStr) > MAXLOGLINESIZE) return;
        if(FileName == NULL) pFile = fopen(EVENT_LOGFILE, "at");
        else if(IsSame(FileName, XSOCKET_LOGFILE)) pFile = fopen(FileName, "ab");
		else pFile = fopen(FileName, "at");
	if (pFile == NULL) return;

	ZeroMemory(cBuffer, sizeof(cBuffer));

	GetLocalTime(&SysTime);
	wsprintf(cBuffer, "(%4d:%2d:%2d:%2d:%2d) - ", SysTime.wYear, SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute);
	strcat(cBuffer, cStr);
	strcat(cBuffer, "\n");

	fwrite(cBuffer, 1, strlen(cBuffer), pFile);
	fclose(pFile);
}

void Assertion(const char * assertion, const char * file, const uint32 line)
{
	char buffer[MAXLOGLINESIZE+100];

	sprintf(buffer, "%s(%i)(%d.%d): ASSERTION FAILED:  %s", file, line,
		UPPER_VERSION, LOWER_VERSION, assertion); 
	PutLogFileList((const char*)buffer, DEBUG_LOGFILE);
}
//=============================================================================
/*void PutLogList(char * cMsg, BYTE MsgLvl, bool PutOnFile, char *FileName)
{
        if(strlen(cMsg) <= MAXLOGMSGSIZE)
          {
           G_cMsgUpdated = TRUE;
           LogMsg.CurMsg++;
           if(LogMsg.CurMsg >= MAXLOGMSGS) LogMsg.CurMsg = 0;
           ZeroMemory(LogMsg.Message[LogMsg.CurMsg], sizeof(LogMsg.Message[LogMsg.CurMsg]));
           SafeCopy(LogMsg.Message[LogMsg.CurMsg], cMsg);
           LogMsg.MsgLvl[LogMsg.CurMsg] = MsgLvl;
           UpdateScreen();
          }
        else if(strlen(cMsg) > MAXLOGLINESIZE) return;
        if(PutOnFile == TRUE) PutLogFileList(cMsg, FileName);
}*/

void PutLogList(const char * cMsg)
{
	printf(cMsg);
	printf("\n");
	G_cMsgUpdated = TRUE;
	PutLogFileList(cMsg, ADMIN_LOGFILE);
	SendMessage(List1,(UINT)LB_ADDSTRING,(WPARAM)0,(LPARAM)cMsg);
	if(scrolling)
		SendMessage(List1,(UINT)LB_SETCURSEL,ItemCount,0);
		ItemCount++;
}

void PutLogList(const string msg)
{
	PutLogList(msg.c_str());
}

void LogError(const char * cMsg)
{
	PutLogList("");
	PutLogList(cMsg);
	PutLogList("");
}

void LogError(const string msg)
{
	LogError(msg.c_str());
}

//=============================================================================
BYTE bGetOffsetValue(char * cp, DWORD offset)
{
 char   *pcp;
 BYTE	*bp;

 pcp = (char *)cp;
 pcp += offset;
 bp = (BYTE *)pcp;
 return *bp;
}
//=============================================================================
WORD wGetOffsetValue(char * cp, DWORD offset)
{
 char   *pcp;
 WORD	*wp;

 pcp = (char *)cp;
 pcp += offset;
 wp = (WORD *)pcp;
 return *wp;
}
//=============================================================================
DWORD dwGetOffsetValue(char * cp, DWORD offset)
{
	char   *pcp;
	DWORD	*dwp;

	pcp = (char *)cp;
	pcp += offset;
	dwp = (DWORD *)pcp;
	return *dwp;
}

uint64 ullGetOffsetValue(char * cp, DWORD offset)
{
	char   *pcp;
	uint64	*dwp;

	pcp = (char *)cp;
	pcp += offset;
	dwp = (uint64 *)pcp;
	return *dwp;
}
//=============================================================================
void PutOffsetValue(char * cp, DWORD offset, BYTE size, uint64 value)
{
	BYTE   *bp;
	WORD   *wp;
	DWORD  *dwp;
	uint64  *llp;
	char   *pcp;

	pcp = (char *)cp;
	pcp += offset;
	switch(size)
	{
	case BYTESIZE:
		bp = (BYTE *)pcp;
		*bp = (BYTE)value;
		break;
	case WORDSIZE:
		wp = (WORD *)pcp;
		*wp = (WORD)value;
		break;
	case DWORDSIZE:
		dwp = (DWORD *)pcp;
		*dwp = (DWORD)value;
		break;
	case I64SIZE:
		llp = (UINT64 *)pcp;
		*llp = value;
		break;
	}
}
//=============================================================================
void SafeCopy(char *c1, char *c2, DWORD lenght)
{
 register DWORD dw;
	 
		if(lenght == 0){
			dw = 0;
			if(c2[dw] == NULL) return;
			while(c2[dw] != NULL){
				c1[dw] = c2[dw];
				dw++;
			}
		}
		else for(dw = 0; dw < lenght; dw++) c1[dw] = c2[dw];

		c1[dw] = NULL;
}
//=============================================================================
bool IsSame(char *c1, char *c2)
{
 DWORD size1, size2;
 
		size1 = strlen(c1);
		size2 = strlen(c2);
		if(size1 == size2 && memcmp(c1, c2, size1) == 0) return true;
        else return false;
}
//=============================================================================
