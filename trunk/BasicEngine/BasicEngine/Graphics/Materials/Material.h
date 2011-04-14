/*
Class Material.h: 
*/


#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <assimp.hpp> // C++ importer interface
#include <aiScene.h> // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <cassert>

#include "../../Utility/Resource.h"
#include "../../Utility/ResourceHandle.h"



class cMaterial : public cResource
{
	public:
		cMaterial() { mbLoaded = false; }
		virtual bool Init( const std::string &lacNameID, void * lpMemoryData, int liDataType);
		virtual void Deinit();
		virtual bool IsLoaded() { return mbLoaded; }
		void SetMaterial();
	
	private:
		cResourceHandle mDiffuseTexture;
		bool mbLoaded;
};

#endif
