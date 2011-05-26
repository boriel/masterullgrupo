/*

class Object.h: Contiene los objetos del mundo

*/

#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include "..\..\MathLib\MathLib.h"
#include "..\..\Physics\PhysicsObject.h"

using namespace std;

class cObject
{
	
	public:
		cObject() {}
		//cObject(cObject lObject); //Ya est� definido el constructor de copia
		
		//cObject(cVec3 lPosition, string lsType, string lsModelName, string lsModelFile);

		void Init();
		void Init (cVec3 lPosition, string lsType, string lsModelName, string lsModelFile, cQuaternion lRotacionInicial);
		void Deinit();
		
		virtual void Update( float lfTimestep );
		virtual void Render();
		//virtual void Render(cMatrix &lWorld);
		
		
		//inline string GetName() { return macName; }
		//inline void SetName(const string &lacName) { macName = lacName; }
		inline void SetWorldMatrix(const cMatrix& lWorld) {	mWorldMatrix = lWorld; }
		
		inline cMatrix GetWorldMatrix( const cMatrix& lWorld ) {	return mWorldMatrix; }
		
		inline void SetType (string lsType) { msType = lsType; }
		inline string GetType () { return msType; }
		inline void SetModelName (string lsModelName) { msModelName = lsModelName; }
		inline string GetModelName () {return msModelName; }
		inline void SetModelFile (string lsModelFile) { msModelFile = lsModelFile; }
		inline string GetModelFile () {return msModelFile; }
		inline void SetPosition (cVec3 lPosition) { mPosition = lPosition; }
		inline cVec3 GetPosition () { return mPosition; }
		inline void SetCollision (cVec3 lCollision) { mCollision = lCollision; }  //a mano por ahora NO USADO!
		inline cVec3 GetCollision () { return mCollision; } //a mano por ahora
		inline void SetRotacionInicial (cQuaternion lQuatRot) { mRotacionInicial = lQuatRot; }  
		inline cQuaternion GetRotacionInicial () { return mRotacionInicial; }  

	protected:
		//string macName;
		cMatrix mWorldMatrix;
		
		cVec3 mPosition;
		string msType;
		string msModelName;
		string msModelFile;
	
		
		cPhysicsObject* mPhysicsObject;
		cVec3 mCollision; //temporal para meter los puntos de desde un xml
		float mfScale;  //no se si usarlo, no se usa por ahora ni se pide
		cQuaternion mRotacionInicial;  //NO ES QUATERNION PROPIEAMENTE DICHO, SON LSO DATOS A PELO DEL XML



};



#endif