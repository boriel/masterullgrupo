#ifndef CHASERBASE_H
#define CHASERBASE_H


// Implementa una clase base para perseguidores

#include <stdlib.h>

#include "../../MathLib/Vec/Vec3.h"
#include "behaviourbase.h"
#include "../Character.h"


class cChaserBase: public cBehaviourBase {
protected:
	cCharacter *mpCharacter;
	cVec3 mTarget;

public:
	void SetTarget(const cVec3 &lTarget) { mTarget = lTarget; }
	cChaserBase(): mpCharacter(NULL) {}
	
	// Estos métodos serán comunes a todos los perseguidores
	virtual void Deinit() { mpCharacter = NULL; }
	virtual void Init(cCharacter *lpCharacter);
};


#endif
