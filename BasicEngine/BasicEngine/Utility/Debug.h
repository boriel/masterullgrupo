#ifndef __DEBUG_H__
#define __DEBUG_H__

// Sólo definimos la clase y la macro si está definida la macro _DEBUG (en modo Debug es automático)
#	ifdef _DEBUG


#include <stdio.h>
#include <windows.h>
#include "Singleton.h"

#define _CON_BUFF_SIZE	4096

class cDebug: public cSingleton<cDebug>
{
friend class cSingleton<cDebug>;
private:
	HANDLE mHandle;

	
protected:
	cDebug();

public:
	bool Init(void);
	bool Deinit(void);

	// Escribe en la consola la cadena pasada por parametro
	int WriteStr(const char *s);
};


#define DEBUG_INIT() cDebug::Get().Init()

#define DEBUG_DEINIT() cDebug::Get().Deinit()

#define DEBUG_PRINTF(...) { \
	char BUFFER[_CON_BUFF_SIZE + 1]; \
	sprintf_s(BUFFER, _CON_BUFF_SIZE, __VA_ARGS__); \
	cDebug::Get().WriteStr(BUFFER); \
}
	
#define DEBUG_MSG(...) { \
			DEBUG_PRINTF("%s[%u]: ", __FILE__, __LINE__); \
			DEBUG_PRINTF(__VA_ARGS__); \
			DEBUG_PRINTF("\n"); \
		}

#else

// En modo release, estas macros se traducen a código vacío
#define DEBUG_INIT()  /*  */
#define DEBUG_DEINIT() /*  */
#define DEBUG_PRINTF(...) /*  */
#define DEBUG_MSG(...) /*  */

#	endif



#endif