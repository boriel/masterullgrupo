/*
Class Object: La clase Object contendrá las mallas, los materiales y la matriz de mundo correspondiente. 
							Nuestra clase objeto tendrá un nombre que identificará al objeto, una matriz de mundo y dos vectores que almacenarán las mallas y los materiales.

							

	
*/

#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

#include "..\..\Utilities\ResourceHandle.h"
#include "..\..\MathLib\MathLib.h"


using namespace std;


class cObject
{
	
	public:
		void Init();
		void Deinit();
		
		virtual void Update( float lfTimestep );
		virtual void Render();
		
		inline string GetName() { return macName; }
		inline void SetName(const string &lacName) { macName = lacName; }
		inline void SetWorldMatrix(const cMatrix& lWorld) {	mWorldMatrix = lWorld; }
		
		inline cMatrix GetWorldMatrix( const cMatrix& lWorld ) {	return mWorldMatrix; }
		
		void AddMesh( cResourceHandle lMeshHandle, cResourceHandle lMaterialHandle );

	protected:
		string macName;
		cMatrix mWorldMatrix;

		std::vector<cResourceHandle> mMeshHandles;
		std::vector<cResourceHandle> mMaterialHandles;

};


#endif
