
#include "Material.h"

#include "MaterialData.h"
#include "../../Utility/FileUtils.h"
#include "../../Graphics/Textures/TextureManager.h"
#include "../../Graphics/Textures/Texture.h"
#include "../../Graphics/GLHeaders.h"


#include "../Effects//EffectManager.h"
#include "../Effects//Effect.h"
#include "../GraphicManager.h"
#include "../Camera.h"
#include "../../Game/Game.h"
#include "../../Utility/Debug.h"


struct cAssimpTextureMaping
{
	aiTextureType mTextureType;
	std::string macPrefix;
};

//Prefijos de las texturas
static cAssimpTextureMaping kacTextureMapping[] =
{
	{ aiTextureType_DIFFUSE, "Diffuse_" },			// The texture is combined with the result of the diffuse lighting equation.
	{ aiTextureType_SPECULAR, "Specular_" },		// The texture is combined with the result of the specular lighting equation.
	{ aiTextureType_AMBIENT, "Ambient_" },			// The texture is combined with the result of the ambient lighting equation.
	{ aiTextureType_EMISSIVE, "Emissive_" },		// The texture is added to the result of the lighting calculation. It isn't influenced by incoming light.
	{ aiTextureType_HEIGHT, "Height_" },				// The texture is a height map. By convention, higher gray-scale values stand for higher elevations from the base height.
	{ aiTextureType_NORMALS, "Normals_" },			// The texture is a (tangent space) normal-map. Again, there are several conventions for tangent-space normal maps. Assimp does (intentionally) not	distinguish here.
	{ aiTextureType_SHININESS, "Shininess_" },	// The texture defines the glossiness of the material. The glossiness is in fact the exponent of the specular (phong) lighting equation. Usually there is a	conversion function defined to map the linear color values in the	texture to a suitable exponent.
	{ aiTextureType_OPACITY, "Opacity_" },			// The texture defines per-pixel opacity. Usually 'white' means opaque and 'black' means 'transparency'. Or quite the opposite.	{ aiTextureType_DISPLACEMENT, "Displacement_"}, // Displacement	texture. The exact purpose and format is application-dependent. Higher color values stand for higher vertex displacements.
	{ aiTextureType_LIGHTMAP, "Lightmap_" },		// Lightmap texture (aka Ambient Occlusion). Both 'Lightmaps' and dedicated 'ambient occlusion maps' are covered by this material property. The texture contains a scaling value for the final color value of a pixel.	Its intensity is not affected by incoming light.
	{ aiTextureType_REFLECTION, "Reflexion_" }, // Reflection	texture. Contains the color of a perfect mirror reflection. Rarely used, almost never for real-time applications.
	{ aiTextureType_UNKNOWN, "Unknown_" },			// Unknown	texture. A texture reference that does not match any of the	definitions above is considered to be 'unknown'. It is still imported, but is excluded from any further postprocessing.
	{ aiTextureType_NONE, "NONE" }							// Mark for the end of the stucture
};


bool cMaterial::Init( const std::string &lacNameID, void * lpMemoryData, int liDataType)
{
	macFile = "";
	//macFile = "./Data/Scene/dragonsmall.DAE";
	cMaterialData * lpMaterialData = (cMaterialData*)lpMemoryData;
	aiMaterial * lpAiMaterial = lpMaterialData->mpMaterial;
	aiString name;
	lpAiMaterial->Get(AI_MATKEY_NAME,name);
	ReadAllTextures(lpAiMaterial, lpMaterialData);

	// Load the shader using the material name
	char lacEffectName[128];
	strcpy(lacEffectName, name.data);
	char * lacLimit = strstr(lacEffectName, "_");
	if (lacLimit != 0)
		*lacLimit = '\0';
	
	std::stringstream lShaderPath;
	//strcpy(lacEffectName, "simple"); //Puesto a mano
	lShaderPath << "./Data/Shader/" << lacEffectName << ".fx";
	//lShaderPath << "./Data/Shader/simple.fx";  //puesto a mano ver que hay que hacer para pillar el que es
	//mEffect = cEffectManager::Get().LoadResource( lacEffectName, lShaderPath.str() );
	mEffect = cEffectManager::Get().LoadResource(lacEffectName, "./Data/Shader/simple.fx"); //a mano

	assert(mEffect.IsValidHandle());
	mbLoaded = mEffect.IsValidHandle();
	return mEffect.IsValidHandle();


	/*
	//Viejo init
	cMaterialData * lpMaterialData = (cMaterialData*)lpMemoryData;
	aiMaterial * lpAiMaterial = lpMaterialData->mpMaterial;
	aiString lPath;
	unsigned luiUVIndex;
	lpAiMaterial->GetTexture(aiTextureType_DIFFUSE,0,&lPath,0,&luiUVIndex);
	
	std::string lacFilename = cFileUtils::GetFilename(lPath.data);
	std::string lDiffuseTextureFile = lpMaterialData->macPath+"/"+lacFilename;
	//mDiffuseTexture = cTextureManager::Get().LoadResource(lDiffuseTextureFile, lDiffuseTextureFile);
	
	mbLoaded = true;
	return true;
	*/
}



bool cMaterial::Init( const std::string &lacNameID, void * lpMemoryData, int liDataType,
	const std::string &lacMaterialsFile)
{

	TiXmlDocument doc( lacMaterialsFile.c_str() );
	bool lbLoadOk = doc.LoadFile();
	
	if (lbLoadOk) {
		DEBUG_MSG("Materials XML file '%s' Load: OK", lacMaterialsFile.c_str());
	} else {
		DEBUG_MSG("Materials XML file '%s' Load: FAILED", lacMaterialsFile.c_str());
		return false;
	}

	cMaterialData * lpMaterialData = (cMaterialData*)lpMemoryData;
	aiMaterial * lpAiMaterial = lpMaterialData->mpMaterial;
	aiString name;
	lpAiMaterial->Get(AI_MATKEY_NAME,name);
	ReadAllTextures(lpAiMaterial, lpMaterialData);
	
	TiXmlElement* lpElem;
	TiXmlHandle lhRoot(0);
	lpElem = doc.FirstChildElement("Materials");
	assert(lpElem);

	std::string lacEffectName = "";
	std::string lacEffectPath = "";
	std::string lacEffectTech = "";

	lhRoot = TiXmlHandle(lpElem);

	// Read all the Materials and stop when the given name is found or fallback to <default>
	for(lpElem = lhRoot.FirstChild( "Material" ).Element(); lpElem; lpElem = lpElem->NextSiblingElement("Material"))
	{
		std::string lacTmp("<default>");
		
		if ((lpElem->Attribute("name") == lacTmp) && (lacEffectName == "")) {
			lacEffectName = lpElem->Attribute("effectName");
			lacEffectPath = lpElem->Attribute("effectPath");
			lacEffectTech = lpElem->Attribute("technique");
			continue;
		}

		if (lpElem->Attribute("name") == lacNameID ) {
			lacEffectName = lpElem->Attribute("effectName");
			lacEffectPath = lpElem->Attribute("effectPath");
			lacEffectTech = lpElem->Attribute("technique");
			break;
		}
	}

	DEBUG_MSG("Cargando material '%s' con efecto '%s' (%s)", lacNameID.c_str(), lacEffectName.c_str(), lacEffectPath.c_str());
	mEffect = cEffectManager::Get().LoadResource(lacEffectName, lacEffectPath); 
	assert(mEffect.IsValidHandle());
	mbLoaded = mEffect.IsValidHandle();
	return mEffect.IsValidHandle();
}



//Se hizo nuevo para la parte de los materiales del skeleton
bool cMaterial::Init( const std::string &lacNameID, const std::string &lacFile )
{
	// Load an XML with a material
	macFile = lacFile;

	// Load the XML file
	TiXmlDocument doc( lacFile.c_str() );
	bool lbLoadOk = doc.LoadFile();
	
	if ( lbLoadOk )
	{
		OutputDebugString("XML Load: OK\n");
	}
	else
	{
		OutputDebugString("XML Load: FAILED\n");
		return false;
	}

	TiXmlHandle lhDoc(&doc);
	TiXmlElement* lpElem;
	TiXmlHandle lhRoot(0);
	lpElem = lhDoc.FirstChildElement().Element();
	assert(lpElem);

	// save this for later
	lhRoot = TiXmlHandle(lpElem);
	std::string lacEffectName = lhRoot.ToElement()->Attribute("effectName");
	std::string lacEffectPath = lhRoot.ToElement()->Attribute("effectPath");
	mEffect = cEffectManager::Get().LoadResource(lacEffectName, lacEffectPath );
	
	// Read all the animations
	maTextureData.resize(0);
	lpElem=lhRoot.FirstChild( "Texture" ).Element();

	for( lpElem; lpElem; lpElem = lpElem->NextSiblingElement("Texture"))
	{
		cTextureData lData;
		std::string lacTextureFile = lpElem->Attribute("file");
		lData.macShaderTextureID = lpElem->Attribute("name");
		lData.mTexture = cTextureManager::Get().LoadResource(lacTextureFile, lacTextureFile);
		assert(lData.mTexture.IsValidHandle());
		maTextureData.push_back(lData);
	}
	mbLoaded = mEffect.IsValidHandle();

	return mbLoaded;
}




void cMaterial::Deinit()
{

}


/*
Funcion que no está en uso ya
void cMaterial::SetMaterial()
{
	// Set the diffuse texture
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	cTexture * lpTexture = (cTexture*)mDiffuseTexture.GetResource();
	unsigned luiTextureHandle = lpTexture->GetTextureHandle();
	glBindTexture( GL_TEXTURE_2D, luiTextureHandle );
}
*/


//al principio de la función se establece el efecto y la
//technique. Después se establecen los parámetros del programador y al final se recorre
//el array de texturas para setear las texturas en las variables correspondientes
void cMaterial::PrepareRender()
{
	// Set the technique
	assert( mEffect.IsValidHandle() );
	cEffect * lpEffect = (cEffect *)mEffect.GetResource();
	assert( lpEffect );
	lpEffect->SetTechnique("Technique0"); // *** Por ahora siempre se usa esta, luego ya se verá

	// Set Properties
	cMatrix lWVPMatrix = cGraphicManager::Get().GetWVPMatrix();
	lpEffect->SetParam("worldViewProj", lWVPMatrix );
	cCamera * lpCamera = cGraphicManager::Get().GetActiveCamera();
	cVec3 lCameraPos = lpCamera->GetView().GetPosition();
	lpEffect->SetParam("cameraPos", lCameraPos );
	lpEffect->SetParam("time", cGame::Get().GetAcumulatedTime() );

	// Set the textures
	for ( unsigned luiTextureIndex = 0;	luiTextureIndex < maTextureData.size();	++luiTextureIndex )
		lpEffect->SetParam(	maTextureData[luiTextureIndex].macShaderTextureID.c_str(),	maTextureData[luiTextureIndex].mTexture);
	
}


void cMaterial::ReadAllTextures(aiMaterial * lpAiMaterial, cMaterialData * lpMaterialData)
{
	// First pass counts the number of textures to allocate the memory
	unsigned luiTextureCount = 0;
	for (unsigned luiTextureTypeIndex = 0; kacTextureMapping[luiTextureTypeIndex].mTextureType !=	aiTextureType_NONE; ++luiTextureTypeIndex)
	{
		luiTextureCount += lpAiMaterial->GetTextureCount(
		kacTextureMapping[luiTextureTypeIndex].mTextureType);
	}

	// Exit if there is no texture
	if (luiTextureCount == 0)
		return;
	
	// Allocate the memory for the textures
	maTextureData.resize(luiTextureCount);
	
	// Initialize all the textures
	unsigned luiNextTexture = 0;
	for ( unsigned luiTextureTypeIndex = 0;	kacTextureMapping[luiTextureTypeIndex].mTextureType != aiTextureType_NONE; ++luiTextureTypeIndex)
	{
		unsigned luiTextureCount = lpAiMaterial->GetTextureCount(kacTextureMapping[luiTextureTypeIndex].mTextureType);
		for ( unsigned luiTextureIndexInType = 0;	luiTextureIndexInType < luiTextureCount; ++luiTextureIndexInType )
		{
			aiString lPath;
			unsigned luiUVIndex;
			lpAiMaterial->GetTexture(	kacTextureMapping[luiTextureTypeIndex].mTextureType, luiTextureIndexInType,&lPath,0,&luiUVIndex);
			std::string lTextureFile = lpMaterialData->macPath + "/" + lPath.data;
			maTextureData[luiNextTexture].mTexture = cTextureManager::Get().LoadResource(lTextureFile, lTextureFile);
			assert(maTextureData[luiNextTexture].mTexture.IsValidHandle());
			std::stringstream lStream;
			lStream << kacTextureMapping[luiTextureTypeIndex].macPrefix	<< luiTextureIndexInType;
			maTextureData[luiNextTexture].macShaderTextureID = lStream.str();
			++luiNextTexture;
		}
	}
}



//Las funciones EnableFirstPass y EnableNextPass sólo se encargan de propagar la llamada al efecto
bool cMaterial::SetFirstPass()
{
	assert( mEffect.IsValidHandle() );
	cEffect * lpEffect = (cEffect *)mEffect.GetResource();
	assert( lpEffect );
	return lpEffect->SetFirstPass();
}

bool cMaterial::SetNextPass()
{
	assert( mEffect.IsValidHandle() );
	cEffect * lpEffect = (cEffect *)mEffect.GetResource();
	assert( lpEffect );
	return lpEffect->SetNextPass();
}