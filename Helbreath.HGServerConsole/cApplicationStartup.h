#pragma once

#include <winsock2.h>
#include <windows.h>
#include "HG.h"

#define WM_USER_TIMERSIGNAL		WM_USER + 500

class cApplicationStartup
{
public:
	void Startup();
	cApplicationStartup();
	~cApplicationStartup();
private:
	MMRESULT StartTimer(DWORD dwTime);
	HWND CreateBackgroundWindow();
	void InitializeSockets();
	void StartHGServer();
};

