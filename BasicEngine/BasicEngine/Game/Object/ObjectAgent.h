#ifndef __OBJECT_AGENT_H__
#define __OBJECT_AGENT_H__

#include "Object.h"
#include "Behaviour\Behaviour.h"
// Clase que define un objeto con comportamiento

class cObjectAgent: public cObject
{
protected:
    cBehaviour *mpActiveBehaviour;

public:
    inline void SetActiveBehaviour( cBehaviour *lpBehaviour ) { mpActiveBehaviour = lpBehaviour; }
	inline cBehaviour* GetActiveBehaviour() { return mpActiveBehaviour; }
    virtual void cObjectAgent::Update( float lfTimestep );
    virtual void Init();

    float GetYaw(); // Devuelve el ángulo de rotación en el eje X
    float GetPitch(); // Devuelve el ángulo de rotación en el eje Y
    float GetRoll(); // Devuelve el ángulo de rotación en el eje Z

    void SetYaw(float lfYaw);
    void SetPitch(float lfPitch);
    void SetRoll(float lfRoll);

    // Velocidad Angular de Giro
    virtual float GetAngSpeedX();
    virtual float GetAngSpeedY();
    virtual float GetAngSpeedZ();
   
    //Devuelve el vector Front del personaje
	cVec3 GetFront();
		
	//Devuelve el vector Left del personaje.
	cVec3 GetLeft();
		
	//Devuelve el vector Right del personaje
	cVec3 GetRight();

    //Devuelve la velocidad lineal (módulo del vector)
    virtual float GetSpeed();
};

#endif