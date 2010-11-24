#ifdef _DEBUG

#include <string.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#include "Debug.h"

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
	FILE *hf;
	int hCrt;

	if (!AllocConsole())
		return false;

	mHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (mHandle == INVALID_HANDLE_VALUE)
		return false;

	hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	hf = _fdopen(hCrt, "w");
	*stdout = *hf;
	setvbuf( stdout, NULL, _IONBF, 0 );

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