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

	//������ �����ϰ� �ֵ�.
	//���� �� ��� ������ �߰����� �ʾ����Ƿ� ���� ���͸��� ������ ���̴�.
	hFileWrite = CreateFile(
		fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, 0);

	WriteFile(
		hFileWrite, fileData, sizeof(fileData),
		&numOfByteWritten, NULL);
	
	CloseHandle(hFileWrite);
	//���� ���͸��� �����ϰ� �ִ�. C ����̺��� ��Ʈ(Root)�� ����Ǿ���.
	
	//19��° �ٿ��� ������ ������ �����ϰ� �ִ�.
	//�̹����� ���� ������ ��ġ ����(���͸� ����)�� �������� �ʾ����Ƿ�
	//���� ���͸����� ������ ã�´�.
	//�׷��� ������ ���� ���͸� ������ ����Ǿ��ٴ� ���̴�. ���� �� ������ �����ϰ� �ȴ�.
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