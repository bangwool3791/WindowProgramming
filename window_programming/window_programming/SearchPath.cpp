#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[MAX_PATH];
	TCHAR bufFilePath[MAX_PATH];
	LPTSTR lpFilePart;
	DWORD result;

	_tprintf(_T("Insert name of the file to find: "));
	_tscanf(_T("%s"), fileName);

	result = SearchPath(
		NULL, fileName, NULL, MAX_PATH, bufFilePath, &lpFilePart
	);

	if (result == 0)
	{
		_tprintf(_T("File not found! \n"));
	}
	else
	{
		_tprintf(_T("File Name %s"), fileName);
		_tprintf(_T("File Path %s"), bufFilePath);
	}
	return 0;
}