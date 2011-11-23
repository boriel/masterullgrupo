#include "RaceControlManager.h"
#include "ObjectManager.h"
#include "ObjectVehicle.h"
#include "..\..\Graphics\GraphicManager.h"
#include "..\SceneManager.h"
#include <tinystr.h>
#include <tinyxml.h>
#include <vector>

bool cRaceControlManager::Init(string lsFileName) 
{	
	msFileName = lsFileName;
	LoadXml();
	muiTemporizador = 0;
	mIsFinalRace=false;
	return true;
}

void cRaceControlManager::Deinit()
{
	mVehicles.clear();
	mLegs.clear();
}

void cRaceControlManager::VaciarObjetos(){
	mVehicles.clear();
	mLegs.clear();
}

void cRaceControlManager::StartRace(){
	// Aqui posicionaremos los coches en su lugar
	
	// Iniciamos la cuenta atrás
	mCuentaAtras=3;
	// Preparamos la carrera
	mRaceRunning=false;
	muiTemporizador = 0;
	mIsFinalRace=false;
}

void cRaceControlManager::EndRace(){
	mRaceRunning=false;

	// Mostramos la pantalla de puntuación desde el HudManager
	mIsFinalRace=true;
}

char *cRaceControlManager::millisecondsToString(int time){
  int milliseconds = (int)(time % 100);
  int seconds = (int)((time/100) % 60);
  int minutes = (int)((time/6000) % 60);
  int hours = (int)((time/360000) % 24);
  
  char *millisecondsStr=new char();
  if(milliseconds<10)
	sprintf(millisecondsStr,"0%i",milliseconds);
  else
	sprintf(millisecondsStr,"%i",milliseconds);

  char *secondsStr=new char();
  if(seconds<10)
	  sprintf(secondsStr,"0%i",seconds);
  else
	  sprintf(secondsStr,"%i",seconds);

  char *minutesStr=new char();
  if(minutes<10)
	  sprintf(minutesStr,"0%i",minutes);
  else
	  sprintf(minutesStr,"%i",minutes);

  char *hourStr=new char();
	if(hours<10)
		sprintf(hourStr,"0%i",hours);
	else
		sprintf(hourStr,"%i",hours);


	char *timeStr=new char();
  sprintf(timeStr,"%s:%s.%s\n",minutesStr,secondsStr,millisecondsStr);
  return timeStr;
 }

void cRaceControlManager::Update(float lfTimestep)
{	
	// Actualizamos el temporizador
	muiTemporizador++;
	if(mCuentaAtras>0)
		if(muiTemporizador % 100 == 0)mCuentaAtras--;

	if(mRaceRunning){
		for (unsigned luiIndex = 0; luiIndex < cObjectManager::Get().GetCars()->size(); ++luiIndex ) 
		{
			// Cada 100 ticks permitimos que se vuelva a poder cruzar la meta
			if(muiTemporizador - mVehicles[luiIndex]->mTickUltimaVuelta > 500)
				mVehicles[luiIndex]->AumentaVuelta=true;

			typedef std::vector<cObject *> cObjectList;
			cObjectList *lCoches=cObjectManager::Get().GetCars();
			// Comprobamos si algún coche ha pasado la meta
			cPhysicsVehicle *Cajota=((cObjectVehicle *)lCoches->at(luiIndex))->GetPtrPhysicsVehicle();
			btRigidBody *lCoche=Cajota->mpbtCarChassis;

			// Buscamos los puntos de contacto
			btManifoldArray   manifoldArray;
			btBroadphasePairArray& pairArray = mRaceControls[0]->getOverlappingPairCache()->getOverlappingPairArray();
			int numPairs = pairArray.size();

			for (int i=0;i<numPairs;i++){
				 manifoldArray.clear();

				 const btBroadphasePair& pair = pairArray[i];
         
				 //unless we manually perform collision detection on this pair, the contacts are in the dynamics world paircache:
				 btBroadphasePair* collisionPair = cPhysicsManager::Get().GetDynamicsWorld()->getPairCache()->findPair(pair.m_pProxy0,pair.m_pProxy1);
				 if (!collisionPair)
					continue;

				 if (collisionPair->m_algorithm)
					collisionPair->m_algorithm->getAllContactManifolds(manifoldArray);

				 for (int j=0;j<manifoldArray.size();j++){
					btPersistentManifold* manifold = manifoldArray[j];
					btScalar directionSign = manifold->getBody0() == mRaceControls[0] ? btScalar(-1.0) : btScalar(1.0);
					for (int p=0;p<manifold->getNumContacts();p++)
					{
             			const btManifoldPoint&pt = manifold->getContactPoint(p);
						if (pt.getDistance()<0.f){
							const btVector3& ptA = pt.getPositionWorldOnA();
							const btVector3& ptB = pt.getPositionWorldOnB();
							const btVector3& normalOnB = pt.m_normalWorldOnB;
							/// work here
							printf ("Un coche paso la meta!\n");
							for (unsigned luiIndex2 = 0; luiIndex2 < mVehicles.size(); ++luiIndex2 ) {
								if (cObjectManager::Get().GetCars()->at(luiIndex)->GetModelName()==mVehicles.at(luiIndex2)->msModelName){
									// Le añadimos UNA vuelta al coche adecuado
									if(mVehicles[luiIndex]->AumentaVuelta){
										mVehicles[luiIndex]->muiNumLaps++;
										// Si algun coche llega al maximo se acaba la carrera
										if(mVehicles[luiIndex]->muiNumLaps==this->muiMaxLaps){
											EndRace();
										}
										mVehicles[luiIndex]->AumentaVuelta=false;
										// Con esto recordaremos hace cuánto pasamos la meta
										mVehicles[luiIndex]->mTickUltimaVuelta=muiTemporizador;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if (mCuentaAtras==0){
		mRaceRunning=true;
		mCuentaAtras=-1;
		muiTemporizador=0; // Reiniciamos la cuenta
	}
/*	//Update ControlRace info, for every vehicle
	for (unsigned luiIndex = 0; luiIndex < mVehicles.size(); ++luiIndex ) {
		tVehicleControl* lpVehicle = mVehicles[luiIndex];
		cObjectVehicle* lpObject = (cObjectVehicle*) cObjectManager::Get().GetObjectA("Vehicle",lpVehicle->msModelName);
		tLegControl* lpNextLeg = mLegs[ lpVehicle->muiNextLeg ];

		if ( lpObject->GetPosition().DistanceTo(lpNextLeg->mvPoint1) < 10) { //Hemos llegado al leg
			lpVehicle->muiNextLeg++; //Incrementamos el número de Legs
			if (lpVehicle->muiNextLeg == mLegs.size()) { //Hemos terminado un Lap
				lpVehicle->muiNumLaps++; //Incrementamos las vueltas o laps
				lpVehicle->muiNextLeg=0;
				if (lpVehicle->muiNumLaps == muiMaxLaps) { //Fin de la carrera
					//TODO
				}
			}
		}
		lpVehicle->muiKm=lpVehicle->muiNumLaps*mLegs.size()+lpVehicle->muiNextLeg;
	}

	unsigned int luiMaxKm = muiMaxLaps * mLegs.size();
	unsigned int luiSelectedCar = 0;

	//Ordenar los vehiculos de carrera, y actualizar miuOrder
	for (unsigned luiIndex = 0; luiIndex < mVehicles.size(); ++luiIndex )
		mVehicles[luiIndex]->muiOrder=0;

	for (unsigned luiPosition = 1; luiPosition <= mVehicles.size(); ++luiPosition ) {
		for (unsigned luiIndex = 0; luiIndex < mVehicles.size(); ++luiIndex ) {
			if ( (mVehicles[luiIndex]->muiKm<luiMaxKm) && 
				(mVehicles[luiIndex]->muiKm>mVehicles[luiSelectedCar]->muiKm) ) 
				{ luiSelectedCar=luiIndex; }
			mVehicles[luiSelectedCar]->muiOrder=luiPosition;
		}
		luiMaxKm = mVehicles[luiSelectedCar]->muiKm;
	}*/
}

void cRaceControlManager::Render()
{
	for (unsigned luiIndex = 0; luiIndex < mLegs.size(); ++luiIndex ) 
	{
		cGraphicManager::Get().DrawLine(mLegs[luiIndex]->mvPoint1, mLegs[luiIndex]->mvPoint2,cVec3(255,255,0));
	}
}

int cRaceControlManager::GetRaceActualLap(){
	return mPlayerVehicle->muiNumLaps;
}

bool cRaceControlManager::LoadXml(void)
{   //Leemos todos los recursos desde un xml
	TiXmlDocument lDoc;

	lDoc.LoadFile ((char*)msFileName.c_str());
	if (!lDoc.LoadFile())
	{
		OutputDebugString ("[cRaceControlManager] XML Load: FAILED\n");
	}

	//RACE element
	TiXmlElement* lpElementRoot, *lpElementRace;
	lpElementRoot = lDoc.FirstChildElement ("Resources");
	lpElementRace = lpElementRoot->FirstChildElement("Race");

	if (lpElementRace->Attribute("MaxLaps") != NULL) {
		muiMaxLaps = (unsigned int) atoi(lpElementRace->Attribute("MaxLaps"));
	} else { muiMaxLaps=0; }

	//VEHICLES elements
	TiXmlElement *lpElement;
	lpElement =  lpElementRace->FirstChildElement ("Vehicles"); 

	for (lpElement=lpElement->FirstChildElement("Vehicle"); lpElement; lpElement=lpElement->NextSiblingElement()) 
	{
		tVehicleControl* lpVehicle = new tVehicleControl;
		lpVehicle->msModelName="Sin Definir";
		lpVehicle->muiNumLaps=0;
		lpVehicle->muiNextLeg=0;
		lpVehicle->isOut=false;
		lpVehicle->muiOrder=0;
		lpVehicle->muiKm=0;
		lpVehicle->isPlayer=false;
		lpVehicle->AumentaVuelta=true;
		lpVehicle->mTickUltimaVuelta=0;

		if (lpElement->Attribute("ModelName") != NULL)
			lpVehicle->msModelName = ((char*)lpElement->Attribute("ModelName"));
		
		// Situamos al coche que maneja el jugador.
		if(cObjectManager::Get().GetObjectPlayer()->GetModelName()==lpVehicle->msModelName){
			lpVehicle->isPlayer = true;
			this->mPlayerVehicle=lpVehicle;
			mVehicles.push_back(lpVehicle);
		}else{
			if(mTipoPartida!=eContrarreloj){
				lpVehicle->isPlayer = false;
				mVehicles.push_back(lpVehicle);
			}
		}		
	}

	//LEGS elements
	lpElement =  lpElementRace->FirstChildElement ("Legs");
	unsigned int luiNextLeg=0;

	for (lpElement=lpElement->FirstChildElement("Leg"); lpElement; lpElement=lpElement->NextSiblingElement()) 
	{
		tLegControl* lpLeg = new tLegControl;
		lpLeg->muiID = luiNextLeg++;
		lpLeg->mvPoint1 = cVec3(0,0,0);
		lpLeg->mvPoint2 = cVec3(0,0,0);
			
		if (lpElement->Attribute("Point1") != NULL) { 
			vector<string> lTokens;
			Tokenize((char*)lpElement->Attribute("Point1"), lTokens, ",");

			lpLeg->mvPoint1.x = (float) strtod(lTokens[0].c_str(), NULL);
			lpLeg->mvPoint1.y = (float) strtod(lTokens[1].c_str(), NULL);
			lpLeg->mvPoint1.z = (float) strtod(lTokens[2].c_str(), NULL);
		}

		if (lpElement->Attribute("Point2") != NULL) { 
			vector<string> lTokens;
			Tokenize((char*)lpElement->Attribute("Point2"), lTokens, ",");

			lpLeg->mvPoint2.x = (float) strtod(lTokens[0].c_str(), NULL);
			lpLeg->mvPoint2.y = (float) strtod(lTokens[1].c_str(), NULL);
			lpLeg->mvPoint2.z = (float) strtod(lTokens[2].c_str(), NULL);
		}
		mLegs.push_back(lpLeg);
	}

	return true;
}

//para hacer un split de un string
void cRaceControlManager::Tokenize(const string& str, vector<string>& tokens,  const string& delimiters)
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);

    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));

        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);

        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

