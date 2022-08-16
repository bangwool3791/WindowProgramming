#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define WORK_MAX	10000
#define THREAD_MAX	50

typedef void(*WORK) (void);

DWORD AddWorkToPool(WORK work);
WORK GetWorkFromPool(void);
DWORD MakeThreadToPoll(DWORD numofThread);
void WorkerThreadFunction(LPVOID pParam);

typedef struct __WorkerThread
{
	HANDLE hThread;
	DWORD idThread;
}WorkerThread;

struct __ThreadPool
{
	WORK workList[WORK_MAX];

	WorkerThread workerThreadList[THREAD_MAX];
	HANDLE workerEventList[THREAD_MAX];
	
	DWORD idxOfCurrentWork;
	DWORD idxOfLastAddedWork;

	DWORD threadIdx;
}gThreadPool;

static HANDLE mutex = NULL;

void InitMutex(void)
{
/*
[in, optional] LPSECURITY_ATTRIBUTES lpMutexAttributes,
[in]           BOOL                  bInitialOwner,
[in, optional] LPCSTR                lpName
*/
	mutex = CreateMutex(NULL, FALSE, NULL);
}

void DeinitMutex(void)
{
	BOOL ret = CloseHandle(mutex);
}

void AcquireMutex(void)
{
	DWORD ret = WaitForSingleObject(mutex, INFINITE);

	if (ret == WAIT_FAILED)
		_tprintf(_T("Error Occur! \n"));
}

void ReleaseMutex(void)
{
	BOOL ret = ReleaseMutex(mutex);
	if (ret == 0)
		_tprintf(_T("Error Occur!\n"));
}

DWORD AddWorkToPool(WORK work)
{
	AcquireMutex();

	if (gThreadPool.idxOfLastAddedWork >= WORK_MAX)
	{
		_tprintf(_T("AddWorkToPool fail! \n"));
		return NULL;
	}

	gThreadPool.workList[gThreadPool.idxOfLastAddedWork++] = work;

	for (DWORD i = 0; i < gThreadPool.threadIdx; ++i)
		SetEvent(gThreadPool.workerEventList[i]);

	ReleaseMutex();
	return 1;
}

WORK GetWorkFromPool()
{
	WORK work = NULL;

	AcquireMutex();

	if (!(gThreadPool.idxOfCurrentWork < gThreadPool.idxOfLastAddedWork))
	{
		ReleaseMutex();
		return NULL;
	}

	work = gThreadPool.workList[gThreadPool.idxOfCurrentWork++];
	ReleaseMutex();
	return work;
}

DWORD MakeThreadToPool(DWORD numOfThread)
{
	InitMutex();
	DWORD capacity = THREAD_MAX - (gThreadPool.threadIdx);

	if (capacity < numOfThread)
		numOfThread = capacity;

	for (DWORD i = 0; i < numOfThread; ++i)
	{
		DWORD idThread;
		HANDLE hThread;
		/*
	  HANDLE CreateEventA(
	  [in, optional] LPSECURITY_ATTRIBUTES lpEventAttributes,
	  [in]           BOOL                  bManualReset,
	  [in]           BOOL                  bInitialState,
	  [in, optional] LPCSTR                lpName);
		*/
		gThreadPool.workerEventList[gThreadPool.threadIdx] = CreateEvent(NULL, FALSE, FALSE, NULL);
		//LPTHREAD_START_ROUTINE Function pointer that has notify thread to start
		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WorkerThreadFunction, (LPVOID)gThreadPool.threadIdx, 0, &idThread);

		gThreadPool.workerThreadList[gThreadPool.threadIdx].hThread = hThread;
		gThreadPool.workerThreadList[gThreadPool.threadIdx].idThread = idThread;
		gThreadPool.threadIdx++;
	}

	return numOfThread;
}

void WorkerThreadFucntion(LPVOID pParam)
{
	WORK workFunction;
	HANDLE event = gThreadPool.workerEventList[(DWORD)pParam];

	while (1)
	{
		//일을 얻어오고 
		workFunction = GetWorkFromPool();
		if (workFunction == NULL)
		{
			WaitForSingleObject(event, INFINITE);
			continue;
		}
		workFunction();
	}
}

void TestFunction()
{
	static int i = 0;
	i++;

	_tprintf(_T("Good Test --%d : Processing thread: %d--\n\n"), i, GetCurrentThreadId());
}

int _tmain(int argc, TCHAR* argv[])
{
	MakeThreadToPoll(3);

	for (int i = 0; i < 100; i++)
	{
		AddWorkToPool(TestFunction);
	}

	Sleep(50000);
	return 0;
}
