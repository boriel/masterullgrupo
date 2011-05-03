/*
Class/struct MaterialData: 
*/

#ifndef MATERIAL_DATA_H
#define MATERIAL_DATA_H

#include <string>

struct aiMaterial; //TODO. ¿Esto está sin definir?

struct cMaterialData {
	std::string macPath;  //directorio
	aiMaterial* mpMaterial;  //nodo del material assimp
};

#endif