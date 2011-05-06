/*
class SkeletalCoreModel: 
Como su nombre indica esta clase representar� a un core de animaci�n, por lo que
deber� interactuar con el core correspondiente de Cal3D que se llama CalCoreModel.
Por lo tanto esta clase ser� un wrapper de la clase de Cal3D.

Por otro lado, el core lo cargaremos haciendo uso de un XML en el que se indique que
ficheros de Cal3D se tienen que cargar. Cal3D tiene varios tipos de ficheros, pero a
nosotros s�lo nos interesan 3 de ellos:
� .csf: Contiene el esqueleto
� .cmf: Contiene una malla
� .caf: Contiene una animaci�n

Por lo tanto el fichero de XML nos indicar� qu� esqueleto, mallas y animaciones deben
cargarse para este core.

*/

/*
#ifndef SKELETAL_CORE_MODEL_H
#define SKELETAL_CORE_MODEL_H


#include <string>

#include "..\..\Utility\Resource.h"

//El enum lo usaremos para almacenar si la animaci�n es un ciclo o una acci�n. La
//estructura permite almacenar toda la informaci�n del XML referente a una animaci�n y
//un identificador que ser� asignado por Cal3D cuando carguemos la animaci�n.
enum eAnimType
{
	eAnimType_Cycle = 0,
	eAnimType_Action
};

struct sAnimationDef
{
	std::string macName;
	std::string macAnimationFile;
	eAnimType meAnimType;
	int miAnimID;
};





class cSkeletalCoreModel : public cResource
{
	public:
		cSkeletalCoreModel() { mpCoreModel = NULL; }
		friend class cSkeletalMesh;
		
		virtual bool Init( const std::string &lacNameID, const std::string &lacFile );
		virtual void Deinit();
		virtual bool IsLoaded() { return (mpCoreModel != NULL); }
		sAnimationDef * GetAnimationDef(const std::string lacAnim);

	private:
		CalCoreModel * GetCoreModel() { return mpCoreModel; }
		void CreateInstance( cSkeletalMesh * lpMesh );
		std::string macFile;
		std::list<sAnimationDef> mAnimationDefs;
		std::list<int> mMeshIndexes;
		CalCoreModel * mpCoreModel;
};











#endif
*/