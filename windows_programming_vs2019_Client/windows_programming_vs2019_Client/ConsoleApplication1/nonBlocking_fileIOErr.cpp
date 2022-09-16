#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

TCHAR strData1[] = _T("1111111111111111111111111111111111111111111111111111111111111111111111111111 ~\n");
TCHAR strData2[] = _T("2222222222222222222222222222222222222222222222222222222222222222222222222222 ~\n");
TCHAR strData3[] = _T("3333333333333333333333333333333333333333333333333333333333333333333333333333 ~\n");

VOID WINAPI FileIOCompletionRoutine(DWORD, DWORD, LPOVERLAPPED);

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("data.txt");

	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, 0);
	
	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("File creation fault! \n"));
		return -1;
	}

	OVERLAPPED overlappedInstOne;
	memset(&overlappedInstOne, 0, sizeof(OVERLAPPED));
	overlappedInstOne.hEvent = (HANDLE)"First I/O";
	WriteFileEx(hFile, strData1, sizeof(strData1), &overlappedInstOne, FileIOCompletionRoutine);
	overlappedInstOne.Offset += _tcslen(strData1) * sizeof(TCHAR);

	//OVERLAPPED overlappedInstTwo;
	memset(&overlappedInstOne, 0, sizeof(OVERLAPPED));
	overlappedInstOne.hEvent = (HANDLE)"Second I/O";
	overlappedInstOne.Offset = overlappedInstOne.Offset;
	WriteFileEx(hFile, strData2, sizeof(strData2), &overlappedInstOne, FileIOCompletionRoutine);
	overlappedInstOne.Offset += _tcslen(strData2) * sizeof(TCHAR);

	//OVERLAPPED overlappedInstThree;
	memset(&overlappedInstOne, 0, sizeof(OVERLAPPED));
	overlappedInstOne.hEvent = (HANDLE)"Third I/O";
	overlappedInstOne.Offset = overlappedInstOne.Offset;
	WriteFileEx(hFile, strData3, sizeof(strData3), &overlappedInstOne, FileIOCompletionRoutine);
	
	SleepEx(INFINITE, TRUE);
	CloseHandle(hFile);
	return 1;
}

VOID WINAPI FileIOCompletionRoutine(DWORD errorCode, DWORD numOfBytesTransfered, LPOVERLAPPED overlapped)
{
	_tprintf(_T("**********File write result **********\n"));
	_tprintf(_T("Error code: %u \n"), errorCode);
	_tprintf(_T("Transfered bytes len: %u \n"), numOfBytesTransfered);
	_tprintf(_T("The other info: %s \n"), (WCHAR*)overlapped->hEvent);
}