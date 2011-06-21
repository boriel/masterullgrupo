/*
Class cScene: (clase cambiada)
Class cModel: Es un conjunto de submodelos
*/

#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "..\..\Utility\Resource.h"
#include "..\..\Utility\ResourceHandle.h"
#include "SubModel.h"

struct aiScene;
struct aiNode;
struct aiMesh;

struct tBounding
{
	cVec3 mvMin;
	cVec3 mvMax;
	cVec3 mvCenter;
	float mfRadius;
};

class cModel : public cResource
{
	public:
		cModel() { mbLoaded = false; }
	
		virtual bool Init( const std::string &lacNameID, const std::string &lacFile );
		virtual void Deinit();
		virtual bool IsLoaded() { return mbLoaded; }
		void Update( float lfTimestep );
		void Render(cMatrix &lWorld);
		void ConvertNodesToObjects( aiNode *lpNode, cMatrix lTransform );
		void ProcessBoundingFile(string lacFile);
		void ProcessBoundingScene(const aiScene* lpScene, string lacFile);
		void ProcessBoundingMesh(aiMesh* lpMesh);
		typedef std::vector<cSubModel *> cObjectList;  //Temporal esta linea
		cObjectList GetObjectList() { return mObjectList; }
		tBounding GetBounding() { return mBounding; }

	private:
		std::string macFile;
		bool mbLoaded;

		typedef std::vector<cResourceHandle> cResourceHandleList;
		typedef cResourceHandleList::iterator cResourceHandleListIt;
		
		cResourceHandleList mMeshList;
		cResourceHandleList mMaterialList;
		
		std::vector<unsigned> mMeshMaterialIndexList; //un vector adicional en la clase escena que nos indicará que material se debe usar para cada malla

		void ProcessScene( const aiScene* lpScene );
		cObjectList mObjectList;
		tBounding mBounding; //Guarda información de Bounding del modelo, la usará cada Object al crear su Physic
};

#endif
