#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

void SoftwareException(void);

int _tmain(int argc, TCHAR* argv[])
{
	SoftwareException();
	_tprintf(_T("End of the _tmain \n"));

	return 0;
}

void SoftwareException(void)
{
	DWORD DefinedException = 0x00;

	DefinedException |= 0x01 << 31;
	DefinedException |= 0x01 << 30;

	DefinedException |= 0x01 << 29;

	DefinedException |= 0x00 << 28;

	DefinedException |= 0x00 << 16;

	DefinedException |=  0x08;

	__try
	{
		_tprintf(_T("Send: exception code: 0x%x \n"), DefinedException);
		RaiseException(DefinedException, 0, NULL, NULL);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		DWORD exptType = GetExceptionCode();
		_tprintf(_T("Recv: exception code: 0x%x \n"), exptType);
	}
}