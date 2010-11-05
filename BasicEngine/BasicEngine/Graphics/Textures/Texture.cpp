#include <cassert>
#include "Texture.h"
#include "../GLHeaders.h"
#include "SOIL/SOIL.h"


//el índice 0 representa un índice inválido para el handle de la textura
bool cTexture::Init( const std::string &lacNameID, const std::string &lacFile )
{
	macFile = lacFile;
	muiTextureHandle = SOIL_load_OGL_texture(
																						macFile.c_str(),
																						SOIL_LOAD_AUTO,  //que se debe encargar de cargar la textura en OpenGL
																						SOIL_CREATE_NEW_ID,  //debe asignar un nuevo identificador de textura
																						SOIL_FLAG_MIPMAPS | //que debe generar los mipmaps de la textura
																						SOIL_FLAG_POWER_OF_TWO | //convertir la textura a potencia de dos
																						SOIL_FLAG_COMPRESS_TO_DXT);  //comprimir la textura a formato dds
	assert( muiTextureHandle != 0 );
	return muiTextureHandle != 0;
}



void cTexture::Deinit()
{
	glDeleteTextures( 1, &muiTextureHandle);
	muiTextureHandle = 0;
}