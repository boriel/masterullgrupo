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
	int miEnemyId; //Id del enemigo
	float mfAwareRadius; //Radio de percepción

public:
	virtual void Init(cCharacter *lpCharacter);
	virtual void Deinit();
	virtual void Update(float lfTimestep);

	void SetTargetWayPoint(const cVec3 &lTargetWayPoint);
	
	//Establece un nuevo valor del radio de percepción
	void SetAwareRadius( float lfAwareRadius);

	//Establece el id del enemigo.
	void SetEnemyId( int liEnemyId );

	inline const cVec3 &GetTargetWayPoint() const { return mTargetWayPoint; }
};


#endif
