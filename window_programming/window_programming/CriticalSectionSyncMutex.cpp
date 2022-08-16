
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 6

LONG gTotalCount = 0;
//뮤텍스 -> 커널 오브젝트이므로 HANDLE 타입의 변수에 그 핸들값을 저장하는 것은 당연하다.
HANDLE hMutex;

void IncreaseCount()
{
	//뮤텍스를 얻기 위해 WaitForSingleObject 함수 호출
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

	//뮤텍스 생성
	//2인자 FALSE 따라서 뮤텍스는 그 누구에게도 소유되지 않은 상태로 생성
	//다시 말하면 Signaled 상태로 뮤텍스 생성
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
	//할당받은 리소스의 해제
	//할당된 커널 오브젝트 소멸(Usage Count = 0이므로)
	CloseHandle(hMutex);
	return 0;
}