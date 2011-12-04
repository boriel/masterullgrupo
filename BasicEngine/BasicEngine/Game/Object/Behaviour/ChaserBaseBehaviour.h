#ifndef __CHASERBASEBEHAVIOUR_H__
#define __CHASERBASEBEHAVIOUR_H__


// Implementa una clase base para perseguidores

#include <stdlib.h>

#include "../../../MathLib/Vec/Vec3.h"
#include "Behaviour.h"
#include "../ObjectAgent.h"


class cChaserBaseBehaviour: public cBehaviour {
protected:
	cObjectAgent *mpCharacter;
	cVec3 mTarget;
	//cVec3 lDistanceVec;  // Vector de distancia entre el objetivo y el personaje
	//float lfDistance; // Distancia al cuadrado

public:
	void SetTarget(const cVec3 &lTarget);
	cChaserBaseBehaviour(): mpCharacter(NULL) {}
	
	// Estos métodos serán comunes a todos los perseguidores
	virtual void Deinit() { mpCharacter = NULL; }
	virtual void Init(cObjectAgent *lpCharacter);
	inline bool EndPointReached() { return mpCharacter->GetPosition() == mTarget; }
};


#endif
