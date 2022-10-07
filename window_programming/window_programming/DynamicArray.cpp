#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <exception>

#define MAX_PAGE 10

int*	nextPageAddr;
DWORD	pageCnt = 0;
DWORD	pageSize;

int PageFaultExceptionFilter(DWORD);

int _tmain(int argc, TCHAR* argv[])
{
	LPVOID baseAddr;
	int* lpPtr;
	SYSTEM_INFO sSysInfo;
	memset(&sSysInfo, 0, sizeof(SYSTEM_INFO));

	GetSystemInfo(&sSysInfo);

	pageSize = sSysInfo.dwPageSize;

	baseAddr = VirtualAlloc(NULL, MAX_PAGE*pageSize, MEM_RESERVE, PAGE_NOACCESS);
	
	if (baseAddr == NULL)
		_tprintf(_T("VirtualAlloc reserve failed"));

	lpPtr = (int*)baseAddr;
	nextPageAddr = (int*)baseAddr;

	for (int i = 0; i < (MAX_PAGE * pageSize) / sizeof(int); ++i)
	{
		__try
		{
			lpPtr[i] = i;
		}
		__except (PageFaultExceptionFilter(GetExceptionCode()))
		{
			ExitProcess(GetLastError());
		}
	}

	BOOL isSuccess = VirtualFree(baseAddr, 0, MEM_RELEASE);

	if (isSuccess)
		_tprintf(_T("Release succeeded!"));
	else
		_tprintf(_T("Release failed!"));
	
	return 0;
}

int PageFaultExceptionFilter(DWORD exptCode)
{
	if (exptCode != EXCEPTION_ACCESS_VIOLATION)
	{
		_tprintf(_T("Exception code = %d \n"), exptCode);
		return EXCEPTION_EXECUTE_HANDLER;
	}

	_tprintf(_T("Exception is a page fault \n"));

	if (pageCnt >= MAX_PAGE)
	{
		_tprintf(_T("Exception: out of pages \n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}

	LPVOID lpvResult = VirtualAlloc((LPVOID)nextPageAddr, pageSize, MEM_COMMIT, PAGE_READWRITE);

	if (lpvResult == NULL)
	{
		_tprintf(_T("VirtualAlloc failed \n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else
	{
		_tprintf(_T("Allocationg another page. \n"));
	}

	pageCnt++;
 	nextPageAddr += pageSize / sizeof(int);
	return EXCEPTION_CONTINUE_EXECUTION;
}