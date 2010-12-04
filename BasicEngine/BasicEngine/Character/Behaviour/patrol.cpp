#include <stdlib.h>
#include <cassert>
#include "../../Lua/LuaManager.h"
#include "BehaviourManager.h"
#include "patrol.h"


void cPatrol::Init(cCharacter *lpCharacter)
{
	mpBehaviour = (cChaserWithOrientation *)cBehaviourManager::Get().CreateBehaviour(eCHASER_WITH_ORIENTATION);
	mpCharacter = lpCharacter;
	mpCharacter->SetActiveBehaviour(mpBehaviour);	
	mTargetWayPoint = mpCharacter->GetPosition();
	mpBehaviour->Init(lpCharacter);
	mpBehaviour->SetTarget(mTargetWayPoint);
}


void cPatrol::Deinit()
{
	mpBehaviour->Deinit();
	mpCharacter = NULL;
}


void cPatrol::Update(float lfTimestep)
{
	if (!mpBehaviour->EndPointReached())
		mpBehaviour->Update(lfTimestep);
	else { // Llamara función LUA que obtiene el nuevo punto

		
	}	
}


void cPatrol::SetTargetWayPoint(const cVec3 &lTargetWayPoint)
{
	mpBehaviour->SetTarget(mTargetWayPoint);
}


cVec3 cPatrol::NextEndPoint()
{
	float lfX, lfY, lfZ;

	//Introducimos en la pila el nombre de la funcion
	//definida en Lua que queremos llamar
	cLuaManager::Get().PushArg("NextEndPoint");
	//Introducimos en la pila el argumento (ID del Personaje)
	cLuaManager::Get().PushArg(mpCharacter->GetId());

	//Llamamos a la función pasándole un argumento
	//y esta nos devolverá el resultado (3 floats) en la pila de Lua
	lua_call(cLuaManager::Get().GetContext(), 1, 3);
	//Almacenamos el resultado (lo cogemos de la pila)

	cLuaManager::Get().GetRetValue(&lfZ);
	cLuaManager::Get().Pop(1);
	cLuaManager::Get().GetRetValue(&lfY);
	cLuaManager::Get().Pop(1);
	cLuaManager::Get().GetRetValue(&lfX);
	cLuaManager::Get().Pop(1);

	//Devolvemos el resultado
	return cVec3(lfX, lfY, lfZ);
}

