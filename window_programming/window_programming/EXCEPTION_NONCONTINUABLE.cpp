#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BEST_TEST_EXCEPTION ((DWORD)0xE0000008L)

void SoftwareException(void);

int _tmain(int argc, _TCHAR* argv[])
{
	SoftwareException();
	_tprintf(_T("End of the _tmain\n"));
	return 0;
}

void SoftwareException(void)
{
	__try
	{
		RaiseException(BEST_TEST_EXCEPTION, 0, NULL, NULL);
		_tprintf(_T("It's work! \n"));
	}
	__except (EXCEPTION_CONTINUE_EXECUTION)
	{
		DWORD exptType = GetExceptionCode();

		if (exptType == BEST_TEST_EXCEPTION)
		{
			_tprintf(_T("BEST_TEST_EXCEPTION exception occured\n"));
		}
	}
}