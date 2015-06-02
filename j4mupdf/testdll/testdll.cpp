// testdll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <windows.h>

typedef void*(*pfun_j_mu_init_Context)();

int _tmain(int argc, _TCHAR* argv[])
{
	HINSTANCE hdll;
	hdll = LoadLibrary(L"j4mupdf.dll");

	pfun_j_mu_init_Context init;
	if (hdll != NULL)
	{
		init = (pfun_j_mu_init_Context)GetProcAddress(hdll, "j_mu_init_Context");
		if (init)
		{
			init();
		}
	}
	return 0;
}

