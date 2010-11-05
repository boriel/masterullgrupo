#include <string.h>
#include "Debug.h"


#ifdef _DEBUG


// Devuelve el nombre de fichero (ignorando el directorio)
const char *__basename(const char *fname)
{
	const char *result = strrchr(fname, '\\');
	if (result)
		return result + 1;

	return fname;
}


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
	if (FreeConsole())
		return true;

	return false;
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