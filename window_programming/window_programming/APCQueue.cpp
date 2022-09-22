//#define _WIN32_WINNT0x0400

#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

VOID CALLBACK APCProc(ULONG_PTR);

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTread = GetCurrentThread();

	QueueUserAPC(APCProc, hTread, (ULONG_PTR)1);
	QueueUserAPC(APCProc, hTread, (ULONG_PTR)2);
	QueueUserAPC(APCProc, hTread, (ULONG_PTR)3);
	QueueUserAPC(APCProc, hTread, (ULONG_PTR)4);
	QueueUserAPC(APCProc, hTread, (ULONG_PTR)5);

	Sleep(5000);
	SleepEx(INFINITE, TRUE);
	return 0;
}

VOID CALLBACK APCProc(ULONG_PTR dwParam)
{
	_tprintf(_T("Asynchronous procedure call num %u \n"), (DWORD)dwParam);
}