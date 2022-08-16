//#include <stdio.h>
//#include <stdlib.h>
//#include <Windows.h>
//#include <process.h>
//
//#define NUM_OF_GATE 6
//
//LONG gTotalCount = 0;
//
//CRITICAL_SECTION hCriticalSection;
//
//void IncreaseCount()
//{
//	EnterCriticalSection(&hCriticalSection);
//	gTotalCount++;
//	LeaveCriticalSection(&hCriticalSection);
//}
//
//unsigned int WINAPI ThreadProc(LPVOID lpParam)
//{
//	for (DWORD i = 0; i < 1000; i++)
//	{
//		IncreaseCount();
//	}
//	return 0;
//}
//#include <iostream>
//
//int _tmain(int argc, TCHAR* argv[])
//{
//	DWORD dwThreadID[NUM_OF_GATE];
//	HANDLE hTread[NUM_OF_GATE];
//
//	InitializeCriticalSection(&hCriticalSection);
//
//	for (DWORD i = 0; i < NUM_OF_GATE; ++i)
//	{
//		hTread[i] = (HANDLE)
//			_beginthreadex(
//				NULL, 
//				0, 
//				ThreadProc,
//				NULL, 
//				CREATE_SUSPENDED,
//				(unsigned*)&dwThreadID[i]);
//	
//		if (hTread[i] == NULL)
//		{
//			std::cout << "Thread creation fault! \n" << std::endl;
//			return -1;
//		}
//	}
//
//	for (DWORD i = 0; i < NUM_OF_GATE; ++i)
//	{
//		ResumeThread(hTread[i]);
//	}
//
//	WaitForMultipleObjects(NUM_OF_GATE, hTread, TRUE, INFINITE);
//
//	std::cout << "total count : %d \n" << gTotalCount << std::endl;
//
//	for (DWORD i = 0; i < NUM_OF_GATE; ++i)
//	{
//		CloseHandle(hTread[i]);
//	}
//
//	DeleteCriticalSection(&hCriticalSection);
//
//}