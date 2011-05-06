/*
class SkeletalCoreModel: 
Como su nombre indica esta clase representará a un core de animación, por lo que
deberá interactuar con el core correspondiente de Cal3D que se llama CalCoreModel.
Por lo tanto esta clase será un wrapper de la clase de Cal3D.

Por otro lado, el core lo cargaremos haciendo uso de un XML en el que se indique que
ficheros de Cal3D se tienen que cargar. Cal3D tiene varios tipos de ficheros, pero a
nosotros sólo nos interesan 3 de ellos:
– .csf: Contiene el esqueleto
– .cmf: Contiene una malla
– .caf: Contiene una animación

Por lo tanto el fichero de XML nos indicará qué esqueleto, mallas y animaciones deben
cargarse para este core.

*/

/*
#ifndef SKELETAL_CORE_MODEL_H
#define SKELETAL_CORE_MODEL_H


#include <string>

#include "..\..\Utility\Resource.h"

//El enum lo usaremos para almacenar si la animación es un ciclo o una acción. La
//estructura permite almacenar toda la información del XML referente a una animación y
//un identificador que será asignado por Cal3D cuando carguemos la animación.
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