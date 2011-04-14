
#include "Material.h"

#include "MaterialData.h"
#include "../../Utility/FileUtils.h"
#include "../../Graphics/Textures/TextureManager.h"
#include "../../Graphics/Textures/Texture.h"
#include "../../Graphics/GLHeaders.h"

bool cMaterial::Init( const std::string &lacNameID, void * lpMemoryData, int liDataType)
{
	cMaterialData * lpMaterialData = (cMaterialData*)lpMemoryData;
	aiMaterial * lpAiMaterial = lpMaterialData->mpMaterial;
	
	aiString lPath;
	unsigned luiUVIndex;
	lpAiMaterial->GetTexture(aiTextureType_DIFFUSE,0,&lPath,0,&luiUVIndex);
	
	std::string lacFilename = cFileUtils::GetFilename(lPath.data);
	std::string lDiffuseTextureFile = lpMaterialData->macPath+"/"+lacFilename;
	mDiffuseTexture = cTextureManager::Get().LoadResource(lDiffuseTextureFile, lDiffuseTextureFile);
	
	mbLoaded = true;
	return true;
}


void cMaterial::Deinit()
{

}



void cMaterial::SetMaterial()
{
	// Set the diffuse texture
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	cTexture * lpTexture = (cTexture*)mDiffuseTexture.GetResource();
	unsigned luiTextureHandle = lpTexture->GetTextureHandle();
	glBindTexture( GL_TEXTURE_2D, luiTextureHandle );
}
