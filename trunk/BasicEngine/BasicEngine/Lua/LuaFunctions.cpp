#include <cassert>
#include "../Utility/Debug.h"
#include "../Character/CharacterManager.h"
#include "../Character/Behaviour/BehaviourManager.h"
#include "../Character/Behaviour/ChaserBase.h"
#include "../Character/Behaviour/patrol.h"
#include "../Graphics/GraphicManager.h"

#include "LuaManager.h"
#include "LuaFunctions.h"

#include <deque>


// Macro para registrar funciones en Lua
#define REG_LUA_FUNC(x, y) cLuaManager::Get().Register(x, y)


// Usamos el espacio de nombre de LUA para las funciones de C++ que LUA invocará
namespace LUA {


// Esta función crea un personaje en (0, 0, 0) y 
// le pone como meta las coordenadas X, Y, Z
// y la velocidad tangencial y angular pasadas por LUA
int CreatePatrol(lua_State *lpLuaContext)
{
	//Comprobamos que el contexto de Lua no es NULL
	assert( lpLuaContext );

	//Cogemos el numero de argumentos de la pila de Lua
	int liArgCount = lua_gettop( lpLuaContext );

	//Comprobamos que recibimos 5 argumentos
	assert( liArgCount == 5 );

	float lfX = (float)luaL_checknumber(lpLuaContext, 1);
	float lfY = (float)luaL_checknumber(lpLuaContext, 2);
	float lfZ = (float)luaL_checknumber(lpLuaContext, 3);
	float lfSpeed = (float)luaL_checknumber(lpLuaContext, 4);
	float lfAngSpeed = (float)luaL_checknumber(lpLuaContext, 5);
	
	cCharacter *lpCharacter = cCharacterManager::Get().CreateCharacter();
	lpCharacter->Init();
	lpCharacter->SetActiveBehaviour(cBehaviourManager::Get().CreateBehaviour(ePATROL));
	lpCharacter->GetActiveBehaviour()->Init(lpCharacter);
	((cPatrol *)lpCharacter->GetActiveBehaviour())->SetTargetWayPoint(cVec3(lfX, lfY, lfZ));
	lpCharacter->SetSpeed(lfSpeed);
	lpCharacter->SetAngSpeed(lfAngSpeed);

	//DEBUG_MSG("Param1: %f, Param2: %f, Param3: %f\n", lfX, lfY, lfZ);

	// Ponemos el resultado en la pila, para que LUA lo recojaque a
	lua_pushinteger(lpLuaContext, lpCharacter->GetId());

	//Devolvemos el número de valores de retorno
	return 1;
}

// Establece el Objetivo de un caracterd, pasándole su ID
int SetPatrolTarget(lua_State *lpLuaContext)
{
	//Comprobamos que el contexto de Lua no es NULL
	assert( lpLuaContext );

	//Cogemos el numero de argumentos de la pila de Lua
	int liArgCount = lua_gettop( lpLuaContext );

	//Comprobamos que recibimos 4 argumentos
	assert( liArgCount == 4 );

	cCharacter *mpCharacter = cCharacterManager::Get().GetCharacter((int)luaL_checkinteger(lpLuaContext, 1));
	assert(mpCharacter != NULL); // Comprueba que el ID existe

	float lfX = (float)luaL_checknumber(lpLuaContext, 2);
	float lfY = (float)luaL_checknumber(lpLuaContext, 3);
	float lfZ = (float)luaL_checknumber(lpLuaContext, 4);
	
	((cPatrol *)mpCharacter->GetActiveBehaviour())->SetTargetWayPoint(cVec3(lfX, lfY, lfZ));

	//Devolvemos el número de valores de retorno
	return 0;
}


// Dibuja una linea por pantalla
int DrawLine(lua_State *lpLuaContext)
{
	cVec3 lA, lB; // Origen y destino de la linea
	float lfX, lfY, lfZ; // Variables intermedias para capturar valores de LUA

	//Comprobamos que el contexto de Lua no es NULL
	assert( lpLuaContext );
	
	//Cogemos el numero de argumentos de la pila de Lua
	int liArgCount = lua_gettop( lpLuaContext );

	//Comprobamos que recibimos 6 argumentos
	assert( liArgCount == 6 );

	lfX = (float)luaL_checknumber(lpLuaContext, 1);
	lfY = (float)luaL_checknumber(lpLuaContext, 2);
	lfZ = (float)luaL_checknumber(lpLuaContext, 3);
	lA = cVec3(lfX, lfY, lfZ);

	lfX = (float)luaL_checknumber(lpLuaContext, 4);
	lfY = (float)luaL_checknumber(lpLuaContext, 5);
	lfZ = (float)luaL_checknumber(lpLuaContext, 6);
	lB = cVec3(lfX, lfY, lfZ);

	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);
	cGraphicManager::Get().DrawLine(lA, lB, cVec3(1.0f, 1.0f, 0.0f));

	//Devolvemos el número de valores de retorno
	return 0;
}


};


void RegisterLuaFunctions()
{
	REG_LUA_FUNC("CreatePatrol", LUA::CreatePatrol);
	REG_LUA_FUNC("SetPatrolTarget", LUA::SetPatrolTarget);
	REG_LUA_FUNC("DrawLine", LUA::DrawLine);
}

