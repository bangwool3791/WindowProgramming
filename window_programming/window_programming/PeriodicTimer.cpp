
#define _WIN32_WINNT0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;
	//�ι�° ���� FALSE : �ڵ� ���� ��� Ÿ�̸� ������Ʈ
	//FALSE�� ���޵Ǿ�� �ڵ����� Ÿ�̸Ӱ� Non-Signaled ���°� �Ǿ ��ӵǴ� �˶��� ����
	hTimer = CreateWaitableTimer(NULL, TRUE, _T("WaitAbleTimer"));

	if (!hTimer)
	{
		_tprintf(_T("CreateWaitableTimer faield (%d)\n"), GetLastError());
		return 1;
	}

	_tprintf(_T("Waiting for 10 seconds...\n"));

	//5�� �������� �˶��� �︱ ���̴�.
	SetWaitableTimer(hTimer, &liDueTime, 5000, NULL, NULL, FALSE);

	while (1)
	{
		WaitForSingleObject(hTimer, INFINITE);
		//CreateWaitableTimer 2���� TRUE �̸� Signaled->Non-Signaled ������ȯ �ȵ�����
		//printf ��� ���
		_tprintf(_T("Itmer was signaled.\n"));
		MessageBeep(MB_ICONEXCLAMATION);
	}
	return 0;
}