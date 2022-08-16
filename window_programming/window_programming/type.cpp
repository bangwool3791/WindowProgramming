#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

void TYPE(TCHAR* fileName)
{
	TCHAR StringBuff[1024];

	FILE* filePtr = _tfopen(fileName, _T("rt"));

	while (_fgetts(StringBuff, 1024, filePtr))
		_fputts(StringBuff, stdout);
}

int _tmain(int argc, TCHAR* argv[])
{
	if (argc < 2)
		return -1;

	TYPE(argv[1]);

	return 0;
}