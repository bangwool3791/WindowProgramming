#include <stdio.h>
#include <tchar.h>
#include "swap.h"

#pragma comment(lib, "SwapStaticLib.lib")

int _tmain(int argc, TCHAR * argv[])
{
	int a = 10;
	int b = 20;
	_tprintf(_T("Before: %d, %d \n", a, b));
	swap(&a, &b);
	_tprintf(_T("After: %d, %d \n", a, b));
	return 0;
}