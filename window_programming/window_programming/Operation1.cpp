//#include <stdio.h>
//#include <tchar.h>
//#include <Windows.h>
//#include <iostream>
//
//int _tmain(int argc, TCHAR* argv[])
//{
//	STARTUPINFO si = { 0, };
//
//	PROCESS_INFORMATION pi;
//
//	si.cb = sizeof(si);
//	TCHAR command[] = _T("C:\\books\\Excersice\\window_programming\\window_programming\\x64\\Release\\Operation2.exe");
//
//	CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
//
//	DWORD timing = 0;
//
//	while (1)
//	{
//		for (DWORD i = 0; i < 10000; i++)
//			for (DWORD i = 0; i < 10000; i++);
//		
//		_fputts(_T("Operation1.exe \n"), stdout);
//		
//		timing += 1;
//		if (timing == 2)
//		{
//			//pi.hProcess를 통해 커널 오브젝트에 접근
//			SetPriorityClass(pi.hProcess, NORMAL_PRIORITY_CLASS);
//		}
//	}
//	return 0;
//}