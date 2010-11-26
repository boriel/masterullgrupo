#include "ChaserBase.h"

void cChaserBase::Init(cCharacter *lpCharacter)
{
	mpCharacter = lpCharacter;
}


void cChaserBase::SetTarget(const cVec3 &lTarget)
{
	mTarget = lTarget;
}