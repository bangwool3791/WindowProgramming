#pragma once

#include <Windows.h>

#define WORK_MAX  10000
#define THREAD_MAX      50

typedef void(*WORK) (void);

typedef struct __WorkerThread
{
	//스레드 핸들
	HANDLE hThread;
	//스레드 id
	DWORD idThread;
}WorkerThread;

struct __ThreadPool
{
	//Work를 등록하기 위한 배열
	WORK workList[WORK_MAX];
	//Worker Thread 정보 배열(핸들, ID)
	WorkerThread workerThreadList[THREAD_MAX];
	//Worker Event 리스트
	HANDLE workerEventList[THREAD_MAX];
	//대기 1순위 워크 인덱스
	//처리되어야 할 Work의 위치
	DWORD idxOfCurrentWork;
	//마지막 추가 워크 인덱스 + 1
	//새로운 Work가 등록될 때 등록 위치를 가르쳐준다.
	DWORD idxOfLastAddedWork;
	//저장된 쓰레드의 개수 정보
	DWORD threadIdx;
}gThreadPool;

//[예] workerThreadList[3] 등록 쓰레드 workerEventList[3] 저장 이벤트 동기화 오브젝트와 쌍을 이룬다.
//WorkerThread workerThreadList[THREAD_MAX];
//workerEventList 필요 이유 -> 
//쓰레드 일 부여 -> 쓰레드 호출 실행할 함수 지정ㄴ
//쓰레드 할당 된 일 0 -> WaitFor ~ 함수 사용 Blocked 상태
//새로운 일 부여 -> Bloecked -> Run (EventObejct 필요)
//HANDLE workerEventList[THREAD_MAX];

//아래 두 index 증가는 하되 감소는 하지 않는다. 
//따라서 WORK_MAX만큼 일이 등록되는 경우를 생각하면 원형 큐, 워크 등록 표시 등등의 방법으로 문제점을 보안해야한다.
/*
DWORD idxOfCurrentWork;
DWORD idxOfLastAddedWork;
*/