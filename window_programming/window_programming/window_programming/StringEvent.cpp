#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

//������ �ݹ� �Լ�
unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);

TCHAR string[100];
HANDLE hEvent;

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThread;
	DWORD dwThreadID = 0;

	//����ȭ�� ���� �̺�Ʈ ����
	//1. ��� �Ұ�
	//2. manual-reset mode�� ����
	//3. non-signaled ���·� ����
	//4. �̸����� event
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//���� ���� ���� �����ϰ� �����Ƿ�, Signaled ����, �׸��� Non-Signaled ���·��� ������ ��� ���� ó���ؾ��Ѵ�.
	//�̺�Ʈ ������ ���и�
	if (hEvent == NULL)
	{
		_fputts(_T("Event object createion error \n"), stdout);
		return -1;
	}
	///������ ����
	hThread = (HANDLE)_beginthreadex(NULL, 0, OutputThreadFunction, NULL, 0, (unsigned*)&dwThreadID);

	if (hThread == 0)
	{
		_fputts(_T("Thread creation error \n"), stdout);
		return -1;
	}

	_fputts(_T("Insert string: "), stdout);
	_fgetts(string, 30, stdin);
	//�̺�Ʈ signaled 
	//������ ���ſ���
	SetEvent(hEvent);
	//������ �÷ο� ���� �� 
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hEvent);
	CloseHandle(hThread);
	return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpPraram)
{
	//�ռ� ������ �̺�Ʈ ������Ʈ�� Signaled ���°� �� ���� ��ٸ���.
	//������� ���ŷ ����
	WaitForSingleObject(hEvent, INFINITE);
	//������ �÷ο� ����
	_fputts(_T("Output string: "), stdout);
	_fputts(string, stdout);
	return 0;
}