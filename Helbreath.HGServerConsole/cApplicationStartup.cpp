#include "cApplicationStartup.h"
#include <stdio.h>

HWND hwnd = NULL;
CGame *g_gameCopy = NULL;
XSocket *g_pListenSockCopy = NULL;
bool G_bShutdownCopy = FALSE;
MMRESULT G_mmTimerCopy = NULL;

void OnAccept()
{
	g_gameCopy->bAccept(g_pListenSockCopy);
}

void CALLBACK _TimerFunc(UINT wID, UINT wUser, DWORD dwUSer, DWORD dw1, DWORD dw2)
{
	PostMessage(hwnd, WM_USER_TIMERSIGNAL, wID, NULL);
}

LRESULT CALLBACK BackgroundWindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_COMMAND:
		switch (wParam) {
		case 1012:	// Toggle scrolling
			/*if (scrolling)
				scrolling = false;
			else
				scrolling = true;*/
			break;
		case 1013:	// Clear
			//SendMessage(List1, (UINT)LB_RESETCONTENT, 0, 0);
			//ItemCount = 0;
			break;
		case 1010:	// OK
					//CreateBitmap(1,1,1,1,1);
			char commandtxt[100];
			//GetWindowText(Edit1, commandtxt, 100);
			if (commandtxt != NULL) {
				//SetWindowText(Edit1, NULL);
				//SetFocus(Edit1);
				//parseCommand(commandtxt);
			}
			break;
		}
		break;

	case WM_CREATE:
		break;

	case WM_KEYDOWN:
		g_gameCopy->OnKeyDown(wParam, lParam);
		return (DefWindowProc(hWnd, message, wParam, lParam));
		break;

	case WM_KEYUP:
		g_gameCopy->OnKeyUp(wParam, lParam);
		return (DefWindowProc(hWnd, message, wParam, lParam));
		break;

	case WM_USER_STARTGAMESIGNAL:
		g_gameCopy->OnStartGameSignal();
		break;

	case WM_USER_TIMERSIGNAL:
		if (!G_bShutdownCopy) {
			g_gameCopy->OnTimer(NULL);
		}
		break;

	case WM_USER_ACCEPT:
		OnAccept();
		break;

		//case WM_KEYUP:
		//	OnKeyUp(wParam, lParam);
		//	break;

	case WM_PAINT:
		OnPaint();
		break;

	case WM_DESTROY:
		G_bShutdownCopy = TRUE;
		OnDestroy();
		break;

	case WM_CLOSE:
		if (g_gameCopy->bOnClose()) {
			return (DefWindowProc(hWnd, message, wParam, lParam));
		}
		//G_iQuitProgramCount++;
		//if (G_iQuitProgramCount >= 2) {
		//	return (DefWindowProc(hWnd, message, wParam, lParam));
		//}
		break;

	default:
		if (G_bShutdownCopy) {
			break;
		}
		if (message == WM_ONWEBSOCKETEVENT) {
			g_gameCopy->OnWebSocketEvent(message, wParam, lParam);
		}
		if ((message >= WM_ONLOGSOCKETEVENT + 1) && (message <= WM_ONLOGSOCKETEVENT + MAXSUBLOGSOCK)) {
			g_gameCopy->OnSubLogSocketEvent(message, wParam, lParam);
		}
		if ((message >= WM_ONCLIENTSOCKETEVENT) && (message < WM_ONCLIENTSOCKETEVENT + MAXCLIENTS)) {
			g_gameCopy->OnClientSocketEvent(message, wParam, lParam);
		}
		return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return NULL;
}

void cApplicationStartup::Startup()
{
	printf("Starting HGServerConsole \n");
	static unsigned short _usCnt = 0;
	register MSG msg;
	
	InitializeSockets();	
	StartHGServer();

	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS); // get know what it does!

	G_mmTimerCopy = this->StartTimer(TICKDELAY);

	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if (!GetMessage(&msg, NULL, 0, 0)) {
				//return msg.wParam;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			//UpdateScreen();
		}
		else WaitMessage();
	}
}

cApplicationStartup::cApplicationStartup()
{
}

cApplicationStartup::~cApplicationStartup()
{
}

MMRESULT cApplicationStartup::StartTimer(DWORD dwTime)
{
	TIMECAPS caps;
	MMRESULT timerid;

	timeGetDevCaps(&caps, sizeof(caps));
	timeBeginPeriod(caps.wPeriodMin);
	timerid = timeSetEvent(dwTime, 0, _TimerFunc, 0, (UINT)TIME_PERIODIC);

	return timerid;
}

HWND cApplicationStartup::CreateBackgroundWindow()
{
	WNDCLASS wndclass;
	CHAR *ProviderClass = "AsyncSelect";
	HWND Window;
	char cTitle[100];

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = &BackgroundWindowProcess;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = NULL;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = ProviderClass;

	if (RegisterClass(&wndclass) == 0)
	{
		printf("RegisterClass() failed with error %d\n", GetLastError());
		return NULL;
	}
	else {
		printf("RegisterClass() is OK!\n");
	}

	// Create a window
	Window = CreateWindowEx(
		0,
		ProviderClass,
		cTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		NULL,
		NULL);

	if (Window == NULL)
	{
		printf("CreateWindow() failed with error %d\n", GetLastError());
		return NULL;
	}
	else {
		printf("CreateWindow() is OK!\n");
	}
	return Window;
}

void cApplicationStartup::InitializeSockets()
{
	if (_InitWinsock() == FALSE) {
		printf("Socket 2.2 not found! Cannot execute program.", "ERROR", MB_ICONEXCLAMATION | MB_OK);
		PostQuitMessage(0);
		return;
	}
}

void cApplicationStartup::StartHGServer()
{	
	hwnd = CreateBackgroundWindow();

	g_gameCopy = new CGame(hwnd);
	if (g_gameCopy->bInit() == FALSE) {
		printf("(!!!) STOPPED!");
		PutLogList("(!!!) STOPPED!");
		return;
	}

	g_pListenSockCopy = new XSocket(hwnd, SERVERSOCKETBLOCKLIMIT);
	g_pListenSockCopy->bListen(g_gameCopy->m_cGameServerAddr, g_gameCopy->m_iGameServerPort, WM_USER_ACCEPT);

	/*G_sLogCounter = 0;
	ZeroMemory(G_cLogBuffer, sizeof(G_cLogBuffer));*/
}
