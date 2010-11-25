/*
Class Character: Esta clase representa al personaje

*/


#ifndef CHARACTER_H
#define CHARACTER_H


#include "..\MathLib\MathLib.h"
#include "Behaviour\behaviourbase.h"


class cCharacter
{

	private:
		cVec3 mPosition;	//Posición del personaje
		float mfYaw;		//Orientación del personaje (yaw)
		float mfSpeed;		//Velocidad máxima del personaje
		float mfAngSpeed;	//Velocidad angular del personaje
		cBehaviourBase *mpActiveBehaviour;
		
	public:

		void Init(); //Inicializa los valores de los atributos
		void Deinit();//Implementación vacía
		void Update( float lfTimestep ); //Implementación vacía
		
		//Renderiza un punto que representa la posición del personaje y una
		//pequeña línea que parte de dicho punto que representa la orientación
		//del personaje.
		void Render();
		
		//Getters
		inline const cVec3 &GetPosition() const { return mPosition; }
		inline float GetYaw() const { return mfYaw; }
		inline float GetSpeed() const { return mfSpeed; }
		inline float GetAngSpeed() const { return mfAngSpeed; }
		
		
		//Devuelve el vector Front del personaje
		inline cVec3 GetFront() const { return cVec3( sinf(mfYaw), 0.0f, cosf(mfYaw) ); }
		
		//Devuelve el vector Left del personaje.
		inline cVec3 GetLeft() const { return cVec3( sinf(mfYaw + HALF_PI),	0.0f, cosf(mfYaw + HALF_PI) ); }
		
		//Devuelve el vector Right del personaje
		inline cVec3 GetRight() const { return -GetLeft(); }
		
		//Setters
		void SetPosition( const cVec3 &lPosition );
		void SetYaw( float lfYaw );
		void SetSpeed( float lfSpeed );
		void SetAngSpeed( float lfAngSpeed );

		// Constructor de Oficio
		cCharacter();

		inline void SetActiveBehaviour( cBehaviourBase *lpBehaviour ) { mpActiveBehaviour = lpBehaviour; }
		inline cBehaviourBase* GetActiveBehaviour() { return mpActiveBehaviour; }
};





#endif