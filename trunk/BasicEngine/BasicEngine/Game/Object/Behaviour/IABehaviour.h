#include "ChaserBaseBehaviour.h"

#ifndef __IABEHAVIOUR_H__
#define __IABEHAVIOUR_H__

#include "ChaserBaseBehaviour.h"

// Estado de la IA
typedef enum { IA_INITIAL = 0, // Estado inicial (en el INIT)
    IA_START, // Comienzo de la carrera
    IA_WAIT,  // En espera del semáforo
    IA_RUNNING, // En medio de la carrera
    IA_STUCKED, // Coche trabado
    IA_NEXTPOINT, // Siguiente CheckPoint
    IA_END // La carrera ha terminado
} tIAState; // Estados de la IA


class cIABehaviour: public cChaserBaseBehaviour {
private:
    tIAState mIAState;

    // Subrutina que realiza la conducción
    void DriveCar(float lfTimeStep);
    cVec3 mLastPosition;

public:
	virtual void Update(float lfTimestep);
    unsigned muiCurrentPoint;

    cIABehaviour(): 
    mIAState(IA_INITIAL), // Estado inicial (indefinido) de la IA
    cChaserBaseBehaviour(),  // Llamamos al constructor del ancestro
    muiCurrentPoint(0), // Punto de control (CheckPoint) que se va a perseguir
    mLastPosition(0, 0, 0) // Coordenadas de la posición anterior
    {}

    virtual bool Init(cObjectAgent *lpCharacter);
    inline void setIAState(const tIAState lIAState) { mIAState = lIAState; }
    inline tIAState getIAState() { return mIAState; }
    void nextControlPoint(); // Pasa al siguiente punto de control
};


#endif
