#include "FileUtils.h"


//Recorre la cadena al revés buscando una barra. Si la encuentra,
//devuelve los caracteres que están delante de la barra.
std::string cFileUtils::GetDirectory(const std::string lacFile)
{
	for (int liCharIndex=lacFile.length()-1;liCharIndex >= 0;--liCharIndex)
	{
		if (lacFile[liCharIndex] == '\\' || lacFile[liCharIndex] == '/')
			return lacFile.substr(0, liCharIndex);
	}

	return "";
}

//para extraer el nombre del fichero de la ruta
std::string cFileUtils::GetFilename(const std::string lacFile)
{
	for (int liCharIndex=lacFile.length()-1;liCharIndex>=0;--liCharIndex)
	{
		if (lacFile[liCharIndex] == '\\' || lacFile[liCharIndex] == '/')
			return lacFile.substr(liCharIndex + 1);
	}
	return lacFile;
}