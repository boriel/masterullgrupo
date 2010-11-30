#include <cassert>
#include "../Utility/Debug.h"
#include "../Character/CharacterManager.h"
#include "../Character/Behaviour/BehaviourManager.h"
#include "../Character/Behaviour/ChaserBase.h"

#include "LuaManager.h"
#include "LuaFunctions.h"


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

	float liX = (float)luaL_checknumber(lpLuaContext, 1);
	float liY = (float)luaL_checknumber(lpLuaContext, 2);
	float liZ = (float)luaL_checknumber(lpLuaContext, 3);
	float liSpeed = (float)luaL_checknumber(lpLuaContext, 4);
	float liAngSpeed = (float)luaL_checknumber(lpLuaContext, 5);
	
	cCharacter *lpCharacter = cCharacterManager::Get().CreateCharacter();
	lpCharacter->Init();
	lpCharacter->SetActiveBehaviour(cBehaviourManager::Get().CreateBehaviour(eCHASER_WITH_ORIENTATION));
	//lpCharacter->SetPosition(cVec3(liX, liY, liZ));
	lpCharacter->GetActiveBehaviour()->Init(lpCharacter);
	((cChaserBase *)lpCharacter->GetActiveBehaviour())->SetTarget(cVec3(liX, liY, liZ));
	lpCharacter->SetSpeed(liSpeed);
	lpCharacter->SetAngSpeed(liAngSpeed);

	DEBUG_MSG("Param1: %f, Param2: %f, Param3: %f\n", liX, liY, liZ);

	lua_pushinteger(lpLuaContext, lpCharacter->GetId());

	//Devolvemos el número de valores de retorno
	return 1;
}

};


void RegisterLuaFunctions()
{
	REG_LUA_FUNC("CreatePatrol", LUA::CreatePatrol);
}

