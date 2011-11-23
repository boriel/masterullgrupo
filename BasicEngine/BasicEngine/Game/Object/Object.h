/*

class Object.h: Contiene los objetos del mundo

*/

#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include "..\..\MathLib\MathLib.h"
#include "..\..\Physics\PhysicsObject.h"
#include "..\..\Physics\PhysicsManager.h"

using namespace std;

class cObject
{
	public:
		cObject() {}
		//cObject(cObject lObject); //Ya está definido el constructor de copia
		
		//cObject(cVec3 lPosition, string lsType, string lsModelName, string lsModelFile);

		void Init();
		void Init (cVec3 lPosition, string lsType, string lsModelName, string lsModelFile, cQuaternion lRotacionInicial, float lScale=1.0);
		void Deinit();
		
		virtual void Update( float lfTimestep );
		virtual void Render();
		//virtual void Render(cMatrix &lWorld);
		virtual void InitPhysics ();
		
		
		//inline string GetName() { return macName; }
		//inline void SetName(const string &lacName) { macName = lacName; }
		inline void SetWorldMatrix(const cMatrix& lWorld) {	mWorldMatrix = lWorld; }
		
		inline cMatrix GetWorldMatrix( const cMatrix& lWorld ) {	return mWorldMatrix; }
		inline cMatrix GetWorldMatrix(void) {	return mWorldMatrix; }
		
		inline void SetType (string lsType) { msType = lsType; }
		inline string GetType () { return msType; }
		inline void SetModelName (string lsModelName) { msModelName = lsModelName; }
		inline string GetModelName () {return msModelName; }
		inline void SetModelFile (string lsModelFile) { msModelFile = lsModelFile; }
		inline string GetModelFile () {return msModelFile; }
		inline void SetPosition (cVec3 lPosition) { mPosition = lPosition; }
		inline cVec3 GetPosition () { return mPosition; }
		inline void SetCollision (cVec3 lCollision) { mCollision = lCollision; }  //TODO: a mano por ahora NO USADO!
		inline cVec3 GetCollision () { return mCollision; } //TODO: a mano por ahora
		inline void SetRotacionInicial (cQuaternion lQuatRot) { mRotacionInicial = lQuatRot; }  
		inline cQuaternion GetRotacionInicial () { return mRotacionInicial; }  
		inline void SetMass (float lfMass) { mfMass = lfMass; }
		inline float GetMass () { return mfMass; }
		inline void SetScale(float lfScale) { mfScale=lfScale;}
		inline float GetScale() { return mfScale;}
		inline void SetPlayer(string lsPlayer) { msPlayer=lsPlayer;}
		inline string GetPlayer() { return msPlayer;}

		//para pruebas de recarga
		inline cVec3 GetPosicionInicial () { return mPosicionInicial; }
		inline void SetPosicionInicial (cVec3 lPosicionInicial) { mPosicionInicial = lPosicionInicial; }
		


		inline cPhysicsObject* GetPtrPhysicsObject () {return mpPhysicsObject; }
		inline void SetPtrPhysicsObject (cPhysicsObject* lPhysicsObject) { mpPhysicsObject = lPhysicsObject; }

	protected:
		cMatrix mWorldMatrix;
		
		cVec3 mPosition;
		string msType;
		string msModelName;
		string msModelFile;
		string msPlayer; // Con esto sabemos quién controla el coche, solo se utilizará en los vehicles
		float mfMass;
		
		cPhysicsObject* mpPhysicsObject;
		cVec3 mCollision; //temporal para meter los puntos desde un xml
		float mfScale;  //no se si usarlo, no se usa por ahora ni se pide
		cQuaternion mRotacionInicial;  //NO ES QUATERNION PROPIEAMENTE DICHO, SON LSO DATOS A PELO DEL XML

		//Pruebas almacenando la posicion inicial para la recarga si se da la vuelta. Si eso habría que hacer por donde mas cerca le quede de la pista
		cVec3 mPosicionInicial;
};

#endif