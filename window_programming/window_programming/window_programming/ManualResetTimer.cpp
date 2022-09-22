#define _WIN32_WINNT 0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;

	//타이머 오브젝트를 생성하고 있다. 이때 얻은 핸들을 인자로 전달하면서 32번째 줄에서는 알람 시간을 
	//설정하고있다.
	hTimer = CreateWaitableTimer(NULL, FALSE, _T("WaitableTimer"));

	if (!hTimer)
	{
		_tprintf(_T("CreateWaitableTimer failed (%d)\n"), GetLastError());
		return 1;
	}
	_tprintf(_T("Waiting for 10 seconds ...\n"));
	//1. 알람 설정 타이머 오브젝트 핸들 
	//2. 알림이 울리는 시간(커널 오브젝트가 Signaled 상태가 되는 시간)을 지정하기 위한 매개변수이다.
	//3. 타이머 주기
	//타이머의 알람을 10초로 설정
	SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, FALSE);

	WaitForSingleObject(hTimer, INFINITE);
	_tprintf(_T("Timer was Sinaled.\n"));
	MessageBeep(MB_ICONEXCLAMATION);
	
	return 0;
}