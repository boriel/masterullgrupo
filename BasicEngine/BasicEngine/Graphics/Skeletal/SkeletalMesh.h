/*
class SkeletalMesh:  es la que nos va permitir ver el esqueleto y asignarle algunas animaciones.


*/

/*
#ifndef SKELETAL_MESH_H
#define SKELETAL_MESH_H

class cSkeletalMesh : public cMesh
{
	public:
		cSkeletalMesh(): cMesh() { }
		friend class cSkeletalCoreModel;
		virtual bool Init( const std::string &lacNameID, void * lpMemoryData, int liDataType);
		virtual void Deinit();
		virtual void Update(float lfTimestep);
		virtual void RenderMesh() { ; }
		virtual bool IsLoaded() { return (mpCal3DModel != NULL); }
		void RenderSkeleton();
		bool PlayAnim(const std::string & lacAnimName, float lfWeight, float lfDelayIn, float lfDelayOut = 0.0f);
		void StopAnim(const std::string & lacAnimName, float lfDelayOut = 0.0f);

	private:
		CalModel * mpCal3DModel;
		cSkeletalCoreModel * mpCoreModel;
};



#endif
*/