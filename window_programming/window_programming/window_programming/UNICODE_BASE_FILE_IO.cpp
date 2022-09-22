#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("data.txt");
	TCHAR fileData[] = _T("Just test string~");
	//파일을 쓰기 모드로 개방
	HANDLE hFile = CreateFile(
		fileName, GENERIC_WRITE, FILE_SHARE_WRITE,
		0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
	);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("File creation fault! \n"));
		return -1;
	}

	DWORD numOfByteWritten = 0;

	WriteFile(hFile, fileData, sizeof(fileData), &numOfByteWritten, NULL);

	_tprintf(_T("Written data size: %u \n"), numOfByteWritten);

	CloseHandle(hFile);

	return 0;
}