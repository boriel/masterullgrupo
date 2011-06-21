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
		void ShowInfo(string lacFile);
		void ShowInfo(const aiScene* lpScene, string lacFile);
		typedef std::vector<cSubModel *> cObjectList;  //Temporal esta linea
		cObjectList GetObjectList() { return mObjectList; }

	private:
		std::string macFile;
		bool mbLoaded;

		typedef std::vector<cResourceHandle> cResourceHandleList;
		typedef cResourceHandleList::iterator cResourceHandleListIt;
		
		cResourceHandleList mMeshList;
		cResourceHandleList mMaterialList;
		
		std::vector<unsigned> mMeshMaterialIndexList; //un vector adicional en la clase escena que nos indicará que material se debe usar para cada malla

		void ProcessScene( const aiScene* lpScene );
		
		//typedef std::vector<cSubModel *> cObjectList;  //la puse publica temporalmente
		cObjectList mObjectList;
		
};


#endif
