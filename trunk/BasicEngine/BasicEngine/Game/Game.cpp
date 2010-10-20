//#include <windows.h>


#include "Game.h"
//#include "..\Utility\Console.h"

#include "..\Window\Window.h"
#include "..\Graphics\GraphicManager.h"


//Inicializa el juego
bool cGame::Init()
{
	mbFinish = false;
	
	//Antes se ponía a mano, ahora lo lee desde xml	
	//mProperties.macApplicationName = "Test 1";
	//mProperties.mbFullscreen = false;
	//mProperties.muiBits = 16;
	//mProperties.muiWidth = 640;
	//mProperties.muiHeight = 480;
	
	LoadResources();  //Load Resources to XML

	bool lbResult = cWindow::Get().Init(mProperties);

	// Init OpenGL
	if ( lbResult )
	{
		lbResult = cGraphicManager::Get().Init( &cWindow::Get() );
		
		// Kill Window
		if (!lbResult)
			cWindow::Get().Deinit();
	}

	//Iniciando la camara
	m3DCamera.Init();
	float lfAspect = (float)mProperties.muiWidth / (float)mProperties.muiHeight;
	m3DCamera.SetPerspective (45.0f, lfAspect,0.1f,100.0f);
	m3DCamera.SetLookAt (cVec3 (5.0f, 5.f, 5.f), cVec3 (0.0f, 0.f, 0.f), cVec3 (0, 1, 0));


	
	return lbResult;
}

//Destrucutor del juego
bool cGame::Deinit()
{
	//bool lbResult = cWindow::Get().Deinit();
	
	bool lbResult = cGraphicManager::Get().Deinit();
	lbResult = lbResult && cWindow::Get().Deinit();
	
	return lbResult;
}


//update del juego
void cGame::Update(float lfTimestep)
{
	//std::string lsTime = "aaa";

	//hacer el contador de 5 segundos

	//OutputDebugString (lsTime.c_str());
	
	cWindow::Get().Update();
	// Check if we need to close the application

	mbFinish = mbFinish || cWindow::Get().GetCloseApplication();
	if (mbFinish)
		return;
	
	

}


//render del juego
void cGame::Render() 
{
	
	//Mostrar el contador

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	
	// Render Here!!

	cGraphicManager::Get().DrawPoint(cVec3 (0,0,-5), cVec3 (1,0,0)); //Creamos un punto de ejemplo
	cGraphicManager::Get().DrawLine(cVec3 (0,1,-2), cVec3 (1,0,-3), cVec3 (0,1,0)); //creamos un ejemplo de una linea


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Activate the 3D Camera
	cGraphicManager::Get().ActivateCamera( &m3DCamera );

	// Set the world matrix
	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);

	//lWorld.LoadTranslation (cVec3 (1, 0, -1.5));
	//cGraphicManager::Get().SetWorldMatrix (lWorld);

	// Render the debug lines
	cGraphicManager::Get().DrawGrid();
	cGraphicManager::Get().DrawAxis();

	cGraphicManager::Get().DrawPoint( cVec3(1.5f, 0.0f, 1.5f), cVec3(1.0f, 0.0f, 1.0f) );
	cGraphicManager::Get().DrawLine( cVec3(-1.5f, 0.0f, -1.5f), cVec3(-1.5f, 0.0f, 1.5f), cVec3(1.0f, 1.0f, 0.0f));



	//otros ejes
	lWorld.LoadTranslation (cVec3 (1, 0, -1.5));
	cGraphicManager::Get().SetWorldMatrix (lWorld);

	// Render the debug lines
	cGraphicManager::Get().DrawGrid();
	cGraphicManager::Get().DrawAxis();


	
	cGraphicManager::Get().SwapBuffer();
	
}



//FUNCTIONS

//Load all resources
void cGame::LoadResources ()
{
	
	if (msFilename == "")
		SetFilename("Config.xml");
	
	LoadPropertiesXML ((char*)msFilename.c_str()); //inicializamos el level 
	
}

// Load file and concatenate with string
void cGame::SetFilename(char *lsFilename)
{
	
	string lsFile (".\\Data\\" + string(lsFilename));
	msFilename = lsFile;
	
}

//Load All properties of XML
bool cGame::LoadPropertiesXML(const char* lacLevelFile)
{

	mDoc.LoadFile (lacLevelFile);
	if (!mDoc.LoadFile())
	{
		OutputDebugString ("XML Load: FAILED\n");
		return false;
	}

	bool lbResul;
	
	lbResul = LoadTagConfigXML();	
	

	return lbResul;
}

//Load Tag Config to XML
bool cGame::LoadTagConfigXML()
{
	
	TiXmlElement *lElement;
	lElement = mDoc.FirstChildElement ("Config");

	
	if (lElement->Attribute("Name") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
		mProperties.macApplicationName = ((char*)lElement->Attribute("Name"));
	else
		return false;

	if (lElement->Attribute("Fullscreen") != NULL)
	{
		string lacName = ((char*)lElement->Attribute("Fullscreen"));
		if ( (lacName == "false") || (lacName == "False") )
			mProperties.mbFullscreen = false;
		else if ( (lacName == "true") || (lacName == "True"))
			mProperties.mbFullscreen = true;
		else
			return false;
	}
	else
		return false;

	if (lElement->Attribute("Bits") != NULL ) 
		mProperties.muiBits = atoi (lElement->Attribute("Bits"));
	else
		return false;
	

	if (lElement->Attribute("Width") != NULL ) 
		mProperties.muiWidth = atoi (lElement->Attribute("Width"));
	else
		return false;

	if (lElement->Attribute("Height") != NULL )
		mProperties.muiHeight = atoi (lElement->Attribute("Height"));
	else
		return false;

	return true;
}
