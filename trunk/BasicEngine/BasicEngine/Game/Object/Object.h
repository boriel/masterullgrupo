/*

class Object.h: Contiene los objetos del mundo

*/

#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include "..\..\MathLib\MathLib.h"

using namespace std;

class cObject
{
	
	public:
		void Init();
		void Deinit();
		
		//virtual void Update( float lfTimestep );
		////virtual void Render();
		//virtual void Render(cMatrix &lWorld);
		
		//inline string GetName() { return macName; }
		//inline void SetName(const string &lacName) { macName = lacName; }
		inline void SetWorldMatrix(const cMatrix& lWorld) {	mWorldMatrix = lWorld; }
		
		inline cMatrix GetWorldMatrix( const cMatrix& lWorld ) {	return mWorldMatrix; }
		
		inline void SetType (string lsType) { msType = lsType; }
		inline void SetModelName (string lsModelName) { msModelName  = lsModelName; }
		inline string GetModelName () {return msModelName; }
		inline void SetModelFile (string lsModelFile) { msModelFile  = lsModelFile; }
		inline string GetModelFile () {return msModelFile; }
		inline void SetPosition (cVec3 lPosition) { mPosition  = lPosition; }
		

	protected:
		//string macName;
		cMatrix mWorldMatrix;
		
		cVec3 mPosition;
		string msType;
		string msModelName;
		string msModelFile;
	
		



};



#endif