#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100
TCHAR fileData[] = _T("abcdefghijkmnopqrstuvwxyz");

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("abcd.dat");
	TCHAR readBuf[STRING_LEN];

	SetCurrentDirectory(_T("C:\\"));

	HANDLE hFileWrite;
	HANDLE hFileRead;
	DWORD numOfByteWritten;

	//파일을 생성하고 있따.
	//생성 될 경로 정보를 추가하지 않았으므로 현재 디렉터리에 생성될 것이다.
	hFileWrite = CreateFile(
		fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, 0);

	WriteFile(
		hFileWrite, fileData, sizeof(fileData),
		&numOfByteWritten, NULL);
	
	CloseHandle(hFileWrite);
	//현재 디렉터리를 변경하고 있다. C 드라이브의 루트(Root)로 변경되었다.
	
	//19번째 줄에서 생성한 파일을 개방하고 있다.
	//이번에도 역시 파일의 위치 정보(디렉터리 정보)를 전달하지 않았으므로
	//현재 디렉터리에서 파일을 찾는다.
	//그런데 문제는 현재 디렉터리 정보가 변경되었다는 점이다. 따라서 이 연산은 실패하게 된다.
	hFileRead = CreateFile(
		fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);

	if (hFileRead == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("File open error! \n"));
		return -1;
	}

	ReadFile(hFileRead, readBuf, sizeof(readBuf),
		&numOfByteWritten, NULL);
	_tprintf(_T("%s \n"), readBuf);
	CloseHandle(hFileRead);

	return 0;
}