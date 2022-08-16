
#define _WIN32_WINNT0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;
	//두번째 인자 FALSE : 자동 리셋 모드 타이머 오브젝트
	//FALSE가 전달되어야 자동으로 타이머가 Non-Signaled 상태가 되어서 계속되는 알람에 반응
	hTimer = CreateWaitableTimer(NULL, TRUE, _T("WaitAbleTimer"));

	if (!hTimer)
	{
		_tprintf(_T("CreateWaitableTimer faield (%d)\n"), GetLastError());
		return 1;
	}

	_tprintf(_T("Waiting for 10 seconds...\n"));

	//5초 간격으로 알람이 울릴 것이다.
	SetWaitableTimer(hTimer, &liDueTime, 5000, NULL, NULL, FALSE);

	while (1)
	{
		WaitForSingleObject(hTimer, INFINITE);
		//CreateWaitableTimer 2인자 TRUE 이면 Signaled->Non-Signaled 상태전환 안됨으로
		//printf 계속 출력
		_tprintf(_T("Itmer was signaled.\n"));
		MessageBeep(MB_ICONEXCLAMATION);
	}
	return 0;
}