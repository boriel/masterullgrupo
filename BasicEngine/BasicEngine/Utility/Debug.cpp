#include "Debug.h"

#ifdef _DEBUG


cDebug::cDebug(void)
{
	// Inicializa la clase automáticamente
}

bool cDebug::Init(void)
{
	if (!AllocConsole())
		return false;

	mHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (mHandle == INVALID_HANDLE_VALUE)
		return false;

	return true;
}

bool cDebug::Deinit(void)
{
	// Release the console
	return FreeConsole();
}

int cDebug::WriteStr(const char *s)
{
	DWORD liCount;

	LockWindowUpdate(GetConsoleWindow());
	WriteConsole(mHandle, s, strlen(s), &liCount, NULL);
	LockWindowUpdate(NULL);

	return 0;
}


#endif