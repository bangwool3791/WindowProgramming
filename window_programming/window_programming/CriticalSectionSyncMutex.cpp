
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 6

LONG gTotalCount = 0;
//���ؽ� -> Ŀ�� ������Ʈ�̹Ƿ� HANDLE Ÿ���� ������ �� �ڵ鰪�� �����ϴ� ���� �翬�ϴ�.
HANDLE hMutex;

void IncreaseCount()
{
	//���ؽ��� ��� ���� WaitForSingleObject �Լ� ȣ��
	WaitForSingleObject(hMutex, INFINITE);
	gTotalCount++;
	ReleaseMutex(hMutex);
}

unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	for (DWORD i = 0; i < 1000; i++)
	{
		IncreaseCount();
	}
	return 0;
}

int _tmain(int argc, TCHAR** argv)
{
	DWORD dwThreadIDs[NUM_OF_GATE];
	HANDLE hTreads[NUM_OF_GATE];

	//���ؽ� ����
	//2���� FALSE ���� ���ؽ��� �� �������Ե� �������� ���� ���·� ����
	//�ٽ� ���ϸ� Signaled ���·� ���ؽ� ����
	hMutex = CreateMutex(NULL, FALSE, NULL);

	if (hMutex == NULL)
	{
		_tprintf(_T("CreateMutex error: %d\n"), GetLastError());
	}

	for (DWORD i = 0; i < NUM_OF_GATE; i++)
	{
		hTreads[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadIDs[i]);
	
		if (hTreads[i] == NULL)
		{
			_tprintf(_T("Thread creation fault! \n"));
			return -1;
		}
	}

	for (DWORD i = 0; i < NUM_OF_GATE; ++i)
	{
		ResumeThread(hTreads[i]);
	}

	WaitForMultipleObjects(NUM_OF_GATE, hTreads, TRUE, INFINITE);

	_tprintf(_T("total count: %d \n"), gTotalCount);

	for (DWORD i = 0; i < NUM_OF_GATE; ++i)
	{
		CloseHandle(hTreads[i]);
	}
	//�Ҵ���� ���ҽ��� ����
	//�Ҵ�� Ŀ�� ������Ʈ �Ҹ�(Usage Count = 0�̹Ƿ�)
	CloseHandle(hMutex);
	return 0;
}