#ifndef PATROL_H
#define PATROL_H

#include "../Character.h"
#include "behaviourbase.h"
#include "ChaserWithOrientation.h"

class cPatrol: public cBehaviourBase {

private:
	cCharacter *mpCharacter;
	cChaserWithOrientation *mpBehaviour;
	cVec3 mTargetWayPoint;

	// Funci�n propia para llamar a LUA
	// No podemos usar las templates de funci�n (por ahora) porque
	// no hay ninguna para recibir m�s de tres elementos
	cVec3 NextEndPoint();

public:
	void Init(cCharacter *lpCharacter);
	void Deinit();
	void Update(float lfTimestep);
	void SetTargetWayPoint(const cVec3 &lTargetWayPoint);

	inline const cVec3 &GetTargetWayPoint() const { return mTargetWayPoint; }
};


#endif
