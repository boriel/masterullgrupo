#include "ApplicationProperties.h"

#include <stdio.h>


bool cApplicationProperties::Init() 
{
	
	//Antes se ponía a mano, ahora lo lee desde xml	
	//mProperties.macApplicationName = "Test 1";
	//mProperties.mbFullscreen = false;
	//mProperties.muiBits = 16;
	//mProperties.muiWidth = 640;
	//mProperties.muiHeight = 480;


	string lsFile (".\\Data\\" + string("Config.xml"));
	msFilename = lsFile;

	LoadPropertiesXML ((char*)msFilename.c_str()); //inicializamos el level 

	return true;
}


bool cApplicationProperties::Deinit()
{
	return true;
}

/*
// Load file and concatenate with string
void cApplicationProperties::SetFilename(char *lsFilename)
{
	
	string lsFile (".\\Data\\" + string(lsFilename));
	msFilename = lsFile;
	
}
*/

//Load All properties of XML
bool cApplicationProperties::LoadPropertiesXML(const char* lacLevelFile)
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
bool cApplicationProperties::LoadTagConfigXML()
{
	
	TiXmlElement *lElement;
	lElement = mDoc.FirstChildElement ("Config");

	
	if (lElement->Attribute("Name") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
		macApplicationName = ((char*)lElement->Attribute("Name"));
	else
		return false;

	if (lElement->Attribute("Fullscreen") != NULL)
	{
		string lacName = ((char*)lElement->Attribute("Fullscreen"));
		if ( (lacName == "false") || (lacName == "False") )
			mbFullscreen = false;
		else if ( (lacName == "true") || (lacName == "True"))
			mbFullscreen = true;
		else
			return false;
	}
	else
		return false;

	if (lElement->Attribute("Bits") != NULL ) 
		lElement->Attribute("Bits", (int *)&muiBits);
	else
		return false;
	
	if (lElement->Attribute("Width") != NULL )
		lElement->Attribute("Width", (int *)&muiWidth);
	else
		return false;

	if (lElement->Attribute("Height") != NULL )
		lElement->Attribute("Height", (int *)&muiHeight);
	else
		return false;

	return true;
}
