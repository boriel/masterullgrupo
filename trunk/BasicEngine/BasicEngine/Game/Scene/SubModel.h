/*
Class Object: La clase Object contendrá las mallas, los materiales y la matriz de mundo correspondiente. 
							Nuestra clase objeto tendrá un nombre que identificará al objeto, una matriz de mundo y dos vectores que almacenarán las mallas y los materiales.

							
							Nota: clase cambiada: Es un conjunto de mallas que comparte su matriz local y que contiene la informacion del material

	
*/

#ifndef SUBMODEL_H
#define SUBMODEL_H

#include <string>
#include <vector>

#include "..\..\Utility\ResourceHandle.h"
#include "..\..\MathLib\MathLib.h"



using namespace std;


class cSubModel
{
	
	public:
		void Init();
		void Deinit();
		
		virtual void Update( float lfTimestep );
		//virtual void Render();
		virtual void Render(cMatrix &lWorld);
		
		inline string GetName() { return macName; }
		inline void SetName(const string &lacName) { macName = lacName; }
		inline void SetLocalMatrix(const cMatrix& lWorld) {	mLocalMatrix = lWorld; }
		
		inline cMatrix GetLocalMatrix( const cMatrix& lWorld ) {	return mLocalMatrix; }
		
		void AddMesh( cResourceHandle lMeshHandle, cResourceHandle lMaterialHandle );

		//cMesh* GetMesh (const int liIndex) { return (cMesh *)mMeshHandles[liIndex].GetResource(); }
		cResource* GetResource (const int liIndex) { return mMeshHandles[liIndex].GetResource() ; }
		void TransformVertexsToModelSpace();

	protected:
		string macName;
		cMatrix mLocalMatrix;

		std::vector<cResourceHandle> mMeshHandles;
		std::vector<cResourceHandle> mMaterialHandles;

};


#endif
