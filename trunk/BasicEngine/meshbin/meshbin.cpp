#include <stdlib.h>
#include <stdio.h>

#include "../BasicEngine/Gameplay/Scene/SceneManager.h"
#include "../BasicEngine/Graphics/Meshes/MeshManager.h"
#include "../BasicEngine/Graphics/Meshes/Mesh.h"

void usage(void)
{
	puts("Usage:");
	puts("meshbin <fich_in> <fich_out>");

	return;
	exit(1);
}


int main(int argc, char *argv[])
{
	cResourceHandle lScene;
	cMesh *lpMesh;

	if (argc != 3)
		usage();

	cSceneManager::Get().Init(10);
	cMeshManager::Get().Init(10);
	lScene = cSceneManager::Get().LoadResource("dragon", "dragonsmall.DAE");
	
	printf("%i %i\n", lpMesh->getVertices(), lpMesh->getIndex());

	//mScene = cSceneManager::Get().LoadResource("TestLevel", "./Data/Scene/dragonsmall.DAE");


	return EXIT_SUCCESS;
}
