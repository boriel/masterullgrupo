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
#include "..\..\Graphics\Meshes\Mesh.h"

struct aiScene;
struct aiNode;
struct aiMesh;

struct tBounding
{
	cVec3 mvMin;
	cVec3 mvMax;
	cVec3 mvCenter;
	float mfRadiusInt;
	float mfRadiusExt;
};

class cModel : public cResource
{
	public:
		cModel() { mbLoaded = false; }
	
		virtual bool Init( const std::string &lacNameID, const std::string &lacFile );
		virtual bool Init( const std::string &lacNameID, const std::string &lacFile, float lfScale );
		virtual void Deinit();
		virtual bool IsLoaded() { return mbLoaded; }
		void Update( float lfTimestep );
		void Render(cMatrix &lWorld);
		void ConvertNodesToObjects( aiNode *lpNode, cMatrix lTransform );
		typedef std::vector<cSubModel *> cObjectList;  //Temporal esta linea
		cObjectList GetObjectList() { return mSubModelList; }
		std::vector<tBounding> GetBounding() { return mBounding; }


		//pruebas
		//int GetMeshListID (const unsigned int luiID) { return mMeshList[luiID]; } 
		int GetTamMeshList () { return mMeshList.size(); }
		cResourceHandle GetResourceHandle (const int liIndex) { return mMeshList[liIndex]; }
		cResource* GetResource (const int liIndex) { return mMeshList[liIndex].GetResource(); }
		cMesh* GetMesh (const int liIndex) { return (cMesh*)mMeshList[liIndex].GetResource(); }
		//tBounding ProcessBounding();

	private:
		std::string macFile;
		bool mbLoaded;

		typedef std::vector<cResourceHandle> cResourceHandleList;
		typedef cResourceHandleList::iterator cResourceHandleListIt;
		
		cResourceHandleList mMeshList;
		cResourceHandleList mMaterialList;
		
		std::vector<unsigned> mMeshMaterialIndexList; //un vector adicional en la clase escena que nos indicará que material se debe usar para cada malla
		std::vector<tBounding> mBounding; //Vector que guarda información de Bounding para cada Mesh del Modelo
		

		void ProcessScene( const aiScene* lpScene, float lfScale );
		void ProcessBounding();
//		void ProcessBoundingFile(string lacFile);
//		void ProcessBoundingScene(const aiScene* lpScene, string lacFile);
//		void ProcessBoundingMesh(aiMesh* lpMesh);

		cObjectList mSubModelList; //FIXME: ¿esto para qué está?
};

#endif
