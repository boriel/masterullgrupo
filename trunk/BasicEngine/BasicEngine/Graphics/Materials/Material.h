/*
Class Material.h: 

Las funciones PrepareRender, SetFirstPass y SetNextPass.
Estos tres métodos nos permiten activar las variables del material y activar cada una de
las pasadas. La forma de utilizar estas llamadas se muestra en el siguiente algoritmo:
1) Llamar a PrepareRender para establecer las texturas y parámetros para el
render.
2) Llamar a SetFirstPass para indicarle al efecto que vamos a efectuar la primera
pasada de render.
3) Renderizar la geometría
4) Llamar a SetNextPass para indicar que vamos a efectuar la siguiente pasada. Si
devuelve true es que hay una pasada disponible y volveríamos al paso 3. Si
devuelve false significa que no hay más pasadas de render y hemos acabado de
renderizar la geometría.

*/


#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <assimp.hpp> // C++ importer interface
#include <aiScene.h> // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <cassert>
#include <vector>
#include <sstream>
#include <aiMaterial.h> // C++ importer interface
#include "MaterialData.h"
#include "../../Utility/Resource.h"
#include "../../Utility/ResourceHandle.h"

struct cTextureData {
	std::string macShaderTextureID;
	cResourceHandle mTexture;
};

class cMaterial : public cResource {
public:
	cMaterial() { mbLoaded = false; }
	virtual bool Init( const std::string &lacNameID, void * lpMemoryData, int liDataType);
	virtual void Deinit();
	virtual bool IsLoaded() { return mbLoaded; }
		
	//void SetMaterial();  //Reemplazamos esta función por las 3 funciones de abajo
	void PrepareRender();
	bool SetFirstPass();
	bool SetNextPass();
	
private:
	void ReadAllTextures(aiMaterial * lpAiMaterial, cMaterialData * lpMaterialData);
	std::string macFile;
	std::vector<cTextureData> maTextureData;
	cResourceHandle mEffect;
	//cResourceHandle mDiffuseTexture; //eliminando un textura para hacer una estructura de multiples texturas
	bool mbLoaded;
};

#endif
