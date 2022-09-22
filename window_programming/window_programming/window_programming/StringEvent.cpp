#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

//스레드 콜백 함수
unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);

TCHAR string[100];
HANDLE hEvent;

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThread;
	DWORD dwThreadID = 0;

	//동기화를 위한 이벤트 생성
	//1. 상속 불가
	//2. manual-reset mode로 생성
	//3. non-signaled 상태로 생성
	//4. 이름없는 event
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//수동 리셋 모드로 생성하고 있으므로, Signaled 상태, 그리고 Non-Signaled 상태로의 변경은 모두 수동 처리해야한다.
	//이벤트 생성이 실패면
	if (hEvent == NULL)
	{
		_fputts(_T("Event object createion error \n"), stdout);
		return -1;
	}
	///스레드 생성
	hThread = (HANDLE)_beginthreadex(NULL, 0, OutputThreadFunction, NULL, 0, (unsigned*)&dwThreadID);

	if (hThread == 0)
	{
		_fputts(_T("Thread creation error \n"), stdout);
		return -1;
	}

	_fputts(_T("Insert string: "), stdout);
	_fgetts(string, 30, stdin);
	//이벤트 signaled 
	//스레드 수신에서
	SetEvent(hEvent);
	//스레드 플로우 종료 시 
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hEvent);
	CloseHandle(hThread);
	return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpPraram)
{
	//앞서 생성한 이벤트 오브젝트가 Signaled 상태가 될 것을 기다린다.
	//스레드는 블로킹 상태
	WaitForSingleObject(hEvent, INFINITE);
	//스레드 플로우 시작
	_fputts(_T("Output string: "), stdout);
	_fputts(string, stdout);
	return 0;
}