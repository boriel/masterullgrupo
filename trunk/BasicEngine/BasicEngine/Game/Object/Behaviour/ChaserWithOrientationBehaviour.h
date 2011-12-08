#ifndef __CHASERWITHORIENTATIONBEHAVIOUR_H__
#define __CHASERWITHORIENTATIONBEHAVIOUR_H__

#include "ChaserBaseBehaviour.h"

class cChaserWithOrientationBehaviour: public cChaserBaseBehaviour {

public:
	virtual void Update(float lfTimestep);
    unsigned muiCurrentPoint;

    cChaserWithOrientationBehaviour(): 
        cChaserBaseBehaviour(),  // Llamamos al constructor del ancestro
        muiCurrentPoint(0) {}

    virtual bool Init(cObjectAgent *lpCharacter);
};


#endif
