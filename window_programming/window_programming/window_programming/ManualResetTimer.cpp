#define _WIN32_WINNT 0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;

	//Ÿ�̸� ������Ʈ�� �����ϰ� �ִ�. �̶� ���� �ڵ��� ���ڷ� �����ϸ鼭 32��° �ٿ����� �˶� �ð��� 
	//�����ϰ��ִ�.
	hTimer = CreateWaitableTimer(NULL, FALSE, _T("WaitableTimer"));

	if (!hTimer)
	{
		_tprintf(_T("CreateWaitableTimer failed (%d)\n"), GetLastError());
		return 1;
	}
	_tprintf(_T("Waiting for 10 seconds ...\n"));
	//1. �˶� ���� Ÿ�̸� ������Ʈ �ڵ� 
	//2. �˸��� �︮�� �ð�(Ŀ�� ������Ʈ�� Signaled ���°� �Ǵ� �ð�)�� �����ϱ� ���� �Ű������̴�.
	//3. Ÿ�̸� �ֱ�
	//Ÿ�̸��� �˶��� 10�ʷ� ����
	SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, FALSE);

	WaitForSingleObject(hTimer, INFINITE);
	_tprintf(_T("Timer was Sinaled.\n"));
	MessageBeep(MB_ICONEXCLAMATION);
	
	return 0;
}