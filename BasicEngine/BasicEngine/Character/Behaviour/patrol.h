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

public:
	virtual void Init(cCharacter *lpCharacter);
	virtual void Deinit();
	virtual void Update(float lfTimestep);

	void SetTargetWayPoint(const cVec3 &lTargetWayPoint);

	inline const cVec3 &GetTargetWayPoint() const { return mTargetWayPoint; }
};


#endif
