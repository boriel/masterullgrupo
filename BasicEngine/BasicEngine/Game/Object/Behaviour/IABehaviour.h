#include "ChaserBaseBehaviour.h"

#ifndef __IABEHAVIOUR_H__
#define __IABEHAVIOUR_H__

#include "ChaserBaseBehaviour.h"

class cIABehaviour: public cChaserBaseBehaviour {

public:
	virtual void Update(float lfTimestep);
    unsigned muiCurrentPoint;

    cIABehaviour(): 
        cChaserBaseBehaviour(),  // Llamamos al constructor del ancestro
        muiCurrentPoint(0) {}

    virtual bool Init(cObjectAgent *lpCharacter);
};


#endif
