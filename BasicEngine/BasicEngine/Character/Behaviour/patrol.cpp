#include <stdlib.h>
#include <cassert>
#include "../../Lua/LuaManager.h"
#include "BehaviourManager.h"
#include "patrol.h"


void cPatrol::Init(cCharacter *lpCharacter)
{
	mpBehaviour = (cChaserWithOrientation *)cBehaviourManager::Get().CreateBehaviour(eCHASER_WITH_ORIENTATION);
	mpCharacter = lpCharacter;
	//mpCharacter->SetActiveBehaviour(mpBehaviour);	
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
	if (!mpBehaviour->EndPointReached()) {
		mpBehaviour->Update(lfTimestep);
	} else { // Llamara función LUA que obtiene el nuevo punto
		cLuaManager::Get().CallLua<int, int>("NextEndPoint", mpCharacter->GetId());
		// mpBehaviour->SetTarget(mTargetWayPoint);
	}	
}


void cPatrol::SetTargetWayPoint(const cVec3 &lTargetWayPoint)
{
	mTargetWayPoint = lTargetWayPoint;
	mpBehaviour->SetTarget(mTargetWayPoint);
}


