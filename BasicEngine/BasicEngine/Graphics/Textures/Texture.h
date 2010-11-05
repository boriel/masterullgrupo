/*
class texture

	Heredar� de cResource y deber� implementar las funciones virtuales correspondientes. Para la librer�a SOIL y
	para OpenGL una textura se identifica por un �ndice por lo tanto los atributos de esta clase ser�n el �ndice de 
	la textura y la ruta del fichero.

	La librer�a se encarga de cargar en OpenGL la textura autom�ticamente, pero nosotros tenemos que liberarla usando las
	llamadas de OpenGL. Muchos de los par�metros no son necesarios si estamos usando
	texturas en formato DDS y ralentizar�n la carga de texturas.

*/

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>

#include "../../Utilities/Resource.h"

class cTexture : public cResource
{
	public:
		cTexture() { muiTextureHandle = 0; }
		virtual bool Init( const std::string &lacNameID, const std::string &lacFile );
		virtual void Deinit();
		virtual bool IsLoaded() { return (muiTextureHandle != 0); }
		inline unsigned int GetTextureHandle(){return muiTextureHandle;}
	
	private:
		std::string macFile;
		unsigned int muiTextureHandle;

};


#endif