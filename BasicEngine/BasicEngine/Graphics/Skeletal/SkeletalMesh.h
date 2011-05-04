/*
class cSkeletalMesh: 


Cal3D funciona siguiendo un modelo “core-instance”, esto es que entre
distintos modelos animados de un mismo tipo existen unos datos que son comunes y
otros que dependen de cada instancia.

De esta forma, toda la información que es común se pone en una clase llamada “core” y
toda la información que depende de la instancia se pone en una clase llamada
“instance”. De esta forma se evita duplicar datos en memoria innecesariamente.

esta clase tiene que gestionar dos tipos de resources, por
lo que usaremos el sistema que ya tiene implementado el ResourceManager para
gestionar los cores y añadimos una lista de SkeletalMesh (definiremos esta clase en las
siguientes secciones) que representa la instancia del modelo esqueletal. Para crear las
instancias hemos añadido la función CreateSkeletalMesh, que recibe el nombre del core
que debe usarse para crear la instancia.

*/

/*
#ifndef SKELETAL_MESH
#define SKELETAL_MESH


class cSkeletalMesh;

class cSkeletalManager : public cResourceManager, public cSingleton<cSkeletalManager>
{
	public:
		virtual void Init( unsigned luiMaxSize );
		friend class cSingleton<cSkeletalManager>;
		cSkeletalMesh * CreateSkeletalMesh( const std::string& lacCoreModelName );

	protected:
		cSkeletalManager() { ; } // Protected constructor

	private:
		virtual cResource * LoadResourceInternal( std::string lacNameID, const std::string &lacFile );
};



#endif
*/