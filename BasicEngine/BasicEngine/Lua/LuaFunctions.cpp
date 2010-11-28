#include "LuaManager.h"
#include "LuaFunctions.h"

#include <cassert>

// Macro para registrar funciones en Lua
#define REG_LUA_FUNC(x, y) cLuaManager::Get().Register(x, y)


// Usamos el espacio de nombre de LUA para las funciones de LUA
namespace LUA {

int CreatePatrol(lua_State *lpLuaContext)
{
	//Comprobamos que el contexto de Lua no es NULL
	assert( lpLuaContext );

	//Cogemos el numero de argumentos de la pila de Lua
	int liArgCount = lua_gettop( lpLuaContext );

	//Comprobamos que recibimos 5 argumentos
	assert( liArgCount == 5 );

	//Imprimimos el mensaje por pantalla
	printf("Hello World From C!\n");

	//Devolvemos el número de valores de retorno
	return 0;
}

};


void RegisterLuaFunctions()
{
	REG_LUA_FUNC("CreatePatrol", LUA::CreatePatrol);
}

