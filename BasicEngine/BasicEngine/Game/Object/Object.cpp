#include "Object.h"

#include "..\Scene\Model.h"
#include "..\Scene\ModelManager.h"


void cObject::Render(cMatrix &lWorld)
{
	 
	//Pintando el modelo
	((cModel *)cModelManager::Get().FindResourceA(msModelName).GetResource())->Render(lWorld);

	
}

void cObject::Update( float lfTimestep )
{

}
