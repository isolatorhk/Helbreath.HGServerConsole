#include "cApplicationStartup.h"
#include <stdio.h>

CGame *g_gameCopy = NULL;

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
		//g_game->OnKeyDown(wParam, lParam);
		return (DefWindowProc(hWnd, message, wParam, lParam));
		break;

	case WM_KEYUP:
		//g_game->OnKeyUp(wParam, lParam);
		return (DefWindowProc(hWnd, message, wParam, lParam));
		break;

	case WM_USER_STARTGAMESIGNAL:
		//g_game->OnStartGameSignal();
		break;

	case WM_USER_TIMERSIGNAL:
		/*if (G_bShutdown == FALSE) {
			g_game->OnTimer(NULL);
		}*/
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
		//G_bShutdown = TRUE;
		OnDestroy();
		break;

	case WM_CLOSE:
		/*if (g_game->bOnClose() == TRUE) {
			return (DefWindowProc(hWnd, message, wParam, lParam));
		}*/
		//G_iQuitProgramCount++;
		//if (G_iQuitProgramCount >= 2) {
		//	return (DefWindowProc(hWnd, message, wParam, lParam));
		//}
		break;

	default:
		/*if (G_bShutdown == TRUE) {
			break;
		}*/
		if (message == WM_ONWEBSOCKETEVENT) {
			//g_game->OnWebSocketEvent(message, wParam, lParam);
		}
		if ((message >= WM_ONLOGSOCKETEVENT + 1) && (message <= WM_ONLOGSOCKETEVENT + MAXSUBLOGSOCK)) {
			//g_game->OnSubLogSocketEvent(message, wParam, lParam);
		}
		if ((message >= WM_ONCLIENTSOCKETEVENT) && (message < WM_ONCLIENTSOCKETEVENT + MAXCLIENTS)) {
			//g_game->OnClientSocketEvent(message, wParam, lParam);
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

	/*G_mmTimer = _StartTimer(TICKDELAY);

	G_pListenSock = new class XSocket(G_hWnd, SERVERSOCKETBLOCKLIMIT);
	G_pListenSock->bListen(g_game->m_cGameServerAddr, g_game->m_iGameServerPort, WM_USER_ACCEPT);


	G_sLogCounter = 0;
	ZeroMemory(G_cLogBuffer, sizeof(G_cLogBuffer));*/

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
	HWND hwnd = CreateBackgroundWindow();
	g_gameCopy = new CGame(hwnd);
	/*if (g_gameCopy->bInit() == FALSE) {
		PutLogList("(!!!) STOPPED!");
		return;
	}*/
}
