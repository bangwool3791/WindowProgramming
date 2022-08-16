#pragma once

#include <Windows.h>

#define WORK_MAX  10000
#define THREAD_MAX      50

typedef void(*WORK) (void);

typedef struct __WorkerThread
{
	//������ �ڵ�
	HANDLE hThread;
	//������ id
	DWORD idThread;
}WorkerThread;

struct __ThreadPool
{
	//Work�� ����ϱ� ���� �迭
	WORK workList[WORK_MAX];
	//Worker Thread ���� �迭(�ڵ�, ID)
	WorkerThread workerThreadList[THREAD_MAX];
	//Worker Event ����Ʈ
	HANDLE workerEventList[THREAD_MAX];
	//��� 1���� ��ũ �ε���
	//ó���Ǿ�� �� Work�� ��ġ
	DWORD idxOfCurrentWork;
	//������ �߰� ��ũ �ε��� + 1
	//���ο� Work�� ��ϵ� �� ��� ��ġ�� �������ش�.
	DWORD idxOfLastAddedWork;
	//����� �������� ���� ����
	DWORD threadIdx;
}gThreadPool;

//[��] workerThreadList[3] ��� ������ workerEventList[3] ���� �̺�Ʈ ����ȭ ������Ʈ�� ���� �̷��.
//WorkerThread workerThreadList[THREAD_MAX];
//workerEventList �ʿ� ���� -> 
//������ �� �ο� -> ������ ȣ�� ������ �Լ� ������
//������ �Ҵ� �� �� 0 -> WaitFor ~ �Լ� ��� Blocked ����
//���ο� �� �ο� -> Bloecked -> Run (EventObejct �ʿ�)
//HANDLE workerEventList[THREAD_MAX];

//�Ʒ� �� index ������ �ϵ� ���Ҵ� ���� �ʴ´�. 
//���� WORK_MAX��ŭ ���� ��ϵǴ� ��츦 �����ϸ� ���� ť, ��ũ ��� ǥ�� ����� ������� �������� �����ؾ��Ѵ�.
/*
DWORD idxOfCurrentWork;
DWORD idxOfLastAddedWork;
*/