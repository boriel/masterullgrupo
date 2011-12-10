#include "PhysicsObject.h"


//#include "btBulletDynamicsCommon.h" 
#include "..\Graphics\GraphicManager.h"
#include "PhysicsManager.h"

//Init General, se parece mucho al player y cube, pero irá cambiando
void cPhysicsObject::Init(const cVec3 &lPosition, const cQuaternion &lRotacionInicial) 
{
/*
	//macNameID = lacNameID;
	meType =  ePO_Cube;

	//std::cout << "Cubo.Init()" << std::endl;
	//btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	btDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
  
	
	btVector3 lbtPosition = btVector3(lPosition.x, lPosition.y, lPosition.z);

	//El shape lo creamos de antemano
	//mpbtShape = new btBoxShape(btVector3(0.5, 0.5, 0.5));
	//mpbtShape = new btBoxShape(btVector3(2.2, 1.0, 1.0));  //NPI DE PORQUE NO CARGA DEL FICHERO. VER QUE PASA Y PORQUE NO LEE LOS VALORES del xml y estos si, ME VOY A DORMIR YA
	//mpbtShape = new btBoxShape(btVector3(lCollision.x / 2.0f, lCollision.y / 2.0f, lCollision.z / 2.0f));  //haciendo el cubo con lo pasado en xml

	btQuaternion lbtQuaternion;
	if (lRotacionInicial.w != 0)  //no pusieron ángulo o no rotacion en el xml
		lbtQuaternion =  CambiarEje(lRotacionInicial);
	else
		lbtQuaternion = btQuaternion(0, 0, 0, 1);


  //Funciona el cambio de eje, ya que al parecer desde max y opencollada siempre vienen la z up y no se como cambiarlo en max (y desde el dae es un coñazo a cada rato) pues cambio en codigo

	btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform (lbtQuaternion, lbtPosition));
	//btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform (btQuaternion(0, 0, 0, 1), lbtPosition)); //Funciona para si ya viene todo dado cojonudo en el dae, orientado y todo
	mbtMass = 1;
	//btVector3 fallInertia(0, 0, 0);
	mbtFallInertia = btVector3 (0,0,0);
	mpbtShape->calculateLocalInertia (mbtMass, mbtFallInertia);
	btRigidBody::btRigidBodyConstructionInfo lRigidBodyCI (mbtMass, fallMotionState, mpbtShape, mbtFallInertia);
	//lRigidBodyCI.m_friction = 0.5f;
	mpbtRigidBody = new btRigidBody(lRigidBodyCI);
	lpDynamicsWorld->addRigidBody(mpbtRigidBody);
*/
}

void cPhysicsObject::ApplyImpulse(const cVec3 &lImpulse) 
{
	//btVector3 lbtPosition = mpbtRigidBody->getWorldTransform().getOrigin();
	ApplyImpulse(lImpulse, cVec3(0,0,0));
}

void cPhysicsObject::ApplyImpulse(const cVec3 &lImpulse, const cVec3 &lRelPos) 
{	
	btVector3 lbtPosition = btVector3(lRelPos.x, lRelPos.y, lRelPos.z);
	btVector3 lbtImpulse = btVector3(lImpulse.x, lImpulse.y, lImpulse.z);

	mpbtRigidBody->applyImpulse(lbtImpulse, lbtPosition);
}

/*
//Pintando el centro del objecto
void cPhysicsObject::RenderTransformDebug(const btTransform& lbtTransform, btScalar lbtOrthoLen)
{
	//	
	//btVector3 start = transform.getOrigin();
	//drawLine(start, start+transform.getBasis() * btVector3(orthoLen, 0, 0), btVector3(0.7f,0,0));
	//drawLine(start, start+transform.getBasis() * btVector3(0, orthoLen, 0), btVector3(0,0.7f,0));
	//drawLine(start, start+transform.getBasis() * btVector3(0, 0, orthoLen), btVector3(0,0,0.7f));
	//	


	btVector3 lbtStart = lbtTransform.getOrigin();
	btVector3 lbtEnd1, lbtEnd2, lbtEnd3;

	lbtEnd1 = lbtStart + lbtTransform.getBasis() * btVector3(lbtOrthoLen, 0, 0);
	lbtEnd2 = lbtStart + lbtTransform.getBasis() * btVector3(0, lbtOrthoLen, 0);
	lbtEnd3 = lbtStart + lbtTransform.getBasis() * btVector3(0, 0, lbtOrthoLen);

	cVec3 lStart (lbtStart.getX(), lbtStart.getY(), lbtStart.getZ());
	cVec3 lEnd1 (lbtEnd1.getX(), lbtEnd1.getY(), lbtEnd1.getZ());
	cVec3 lEnd2 (lbtEnd2.getX(), lbtEnd2.getY(), lbtEnd2.getZ());
	cVec3 lEnd3 (lbtEnd3.getX(), lbtEnd3.getY(), lbtEnd3.getZ());

	cGraphicManager::Get().DrawLine(lStart, lEnd1, cVec3(0.7f, 0, 0));
	cGraphicManager::Get().DrawLine(lStart, lEnd2, cVec3(0, 0.7f, 0));
	cGraphicManager::Get().DrawLine(lStart, lEnd3, cVec3(0, 0, 0.7f));
	
	//cGraphicManager::Get().DrawLine(cVec3(0,0,0), cVec3(0,100,0), cVec3(0.7f, 0, 0));
}
*/


/*
//Pintando el cubo
void cPhysicsObject::RenderBoxDebug(const btVector3& lbtMin, const btVector3& lbtMax, const btTransform& lbtTransform, const btVector3& lbtColor)
{
	
	btVector3 lbt01a = lbtTransform * btVector3(lbtMin[0], lbtMin[1], lbtMin[2]);
	btVector3 lbt01b = lbtTransform * btVector3(lbtMax[0], lbtMin[1], lbtMin[2]);
	btVector3 lbt02a = lbtTransform * btVector3(lbtMax[0], lbtMin[1], lbtMin[2]);
	btVector3 lbt02b = lbtTransform * btVector3(lbtMax[0], lbtMax[1], lbtMin[2]);
	btVector3 lbt03a = lbtTransform * btVector3(lbtMax[0], lbtMax[1], lbtMin[2]);
	btVector3 lbt03b = lbtTransform * btVector3(lbtMin[0], lbtMax[1], lbtMin[2]);
	btVector3 lbt04a = lbtTransform * btVector3(lbtMin[0], lbtMax[1], lbtMin[2]);
	btVector3 lbt04b = lbtTransform * btVector3(lbtMin[0], lbtMin[1], lbtMin[2]);
	btVector3 lbt05a = lbtTransform * btVector3(lbtMin[0], lbtMin[1], lbtMin[2]);
	btVector3 lbt05b = lbtTransform * btVector3(lbtMin[0], lbtMin[1], lbtMax[2]);
	btVector3 lbt06a = lbtTransform * btVector3(lbtMax[0], lbtMin[1], lbtMin[2]);
	btVector3 lbt06b = lbtTransform * btVector3(lbtMax[0], lbtMin[1], lbtMax[2]);
	btVector3 lbt07a = lbtTransform * btVector3(lbtMax[0], lbtMax[1], lbtMin[2]);
	btVector3 lbt07b = lbtTransform * btVector3(lbtMax[0], lbtMax[1], lbtMax[2]);
	btVector3 lbt08a = lbtTransform * btVector3(lbtMin[0], lbtMax[1], lbtMin[2]);
	btVector3 lbt08b = lbtTransform * btVector3(lbtMin[0], lbtMax[1], lbtMax[2]);
	btVector3 lbt09a = lbtTransform * btVector3(lbtMin[0], lbtMin[1], lbtMax[2]);
	btVector3 lbt09b = lbtTransform * btVector3(lbtMax[0], lbtMin[1], lbtMax[2]);
	btVector3 lbt10a = lbtTransform * btVector3(lbtMax[0], lbtMin[1], lbtMax[2]);
	btVector3 lbt10b = lbtTransform * btVector3(lbtMax[0], lbtMax[1], lbtMax[2]);
	btVector3 lbt11a = lbtTransform * btVector3(lbtMax[0], lbtMax[1], lbtMax[2]);
	btVector3 lbt11b = lbtTransform * btVector3(lbtMin[0], lbtMax[1], lbtMax[2]);
	btVector3 lbt12a = lbtTransform * btVector3(lbtMin[0], lbtMax[1], lbtMax[2]);
	btVector3 lbt12b = lbtTransform * btVector3(lbtMin[0], lbtMin[1], lbtMax[2]);

	cVec3 lColor (lbtColor.getX(), lbtColor.getY(), lbtColor.getZ());

	cGraphicManager::Get().DrawLine(cVec3 (lbt01a.getX(), lbt01a.getY(), lbt01a.getZ()), cVec3 (lbt01b.getX(), lbt01b.getY(), lbt01b.getZ()), lColor);
	cGraphicManager::Get().DrawLine(cVec3 (lbt02a.getX(), lbt02a.getY(), lbt02a.getZ()), cVec3 (lbt02b.getX(), lbt02b.getY(), lbt02b.getZ()), lColor);
	cGraphicManager::Get().DrawLine(cVec3 (lbt03a.getX(), lbt03a.getY(), lbt03a.getZ()), cVec3 (lbt03b.getX(), lbt03b.getY(), lbt03b.getZ()), lColor);
	cGraphicManager::Get().DrawLine(cVec3 (lbt04a.getX(), lbt04a.getY(), lbt04a.getZ()), cVec3 (lbt04b.getX(), lbt04b.getY(), lbt04b.getZ()), lColor);
	cGraphicManager::Get().DrawLine(cVec3 (lbt05a.getX(), lbt05a.getY(), lbt05a.getZ()), cVec3 (lbt05b.getX(), lbt05b.getY(), lbt05b.getZ()), lColor);
	cGraphicManager::Get().DrawLine(cVec3 (lbt06a.getX(), lbt06a.getY(), lbt06a.getZ()), cVec3 (lbt06b.getX(), lbt06b.getY(), lbt06b.getZ()), lColor);
	cGraphicManager::Get().DrawLine(cVec3 (lbt07a.getX(), lbt07a.getY(), lbt07a.getZ()), cVec3 (lbt07b.getX(), lbt07b.getY(), lbt07b.getZ()), lColor);
	cGraphicManager::Get().DrawLine(cVec3 (lbt08a.getX(), lbt08a.getY(), lbt08a.getZ()), cVec3 (lbt08b.getX(), lbt08b.getY(), lbt08b.getZ()), lColor);
	cGraphicManager::Get().DrawLine(cVec3 (lbt09a.getX(), lbt09a.getY(), lbt09a.getZ()), cVec3 (lbt09b.getX(), lbt09b.getY(), lbt09b.getZ()), lColor);
	cGraphicManager::Get().DrawLine(cVec3 (lbt10a.getX(), lbt10a.getY(), lbt10a.getZ()), cVec3 (lbt10b.getX(), lbt10b.getY(), lbt10b.getZ()), lColor);
	cGraphicManager::Get().DrawLine(cVec3 (lbt11a.getX(), lbt11a.getY(), lbt11a.getZ()), cVec3 (lbt11b.getX(), lbt11b.getY(), lbt11b.getZ()), lColor);
	cGraphicManager::Get().DrawLine(cVec3 (lbt12a.getX(), lbt12a.getY(), lbt12a.getZ()), cVec3 (lbt12b.getX(), lbt12b.getY(), lbt12b.getZ()), lColor);



	//drawLine(trans * btVector3(bbMin[0], bbMin[1], bbMin[2]), trans * btVector3(bbMax[0], bbMin[1], bbMin[2]), color);
	//drawLine(trans * btVector3(bbMax[0], bbMin[1], bbMin[2]), trans * btVector3(bbMax[0], bbMax[1], bbMin[2]), color);
	//drawLine(trans * btVector3(bbMax[0], bbMax[1], bbMin[2]), trans * btVector3(bbMin[0], bbMax[1], bbMin[2]), color);
	//drawLine(trans * btVector3(bbMin[0], bbMax[1], bbMin[2]), trans * btVector3(bbMin[0], bbMin[1], bbMin[2]), color);
	//drawLine(trans * btVector3(bbMin[0], bbMin[1], bbMin[2]), trans * btVector3(bbMin[0], bbMin[1], bbMax[2]), color);
	//drawLine(trans * btVector3(bbMax[0], bbMin[1], bbMin[2]), trans * btVector3(bbMax[0], bbMin[1], bbMax[2]), color);
	//drawLine(trans * btVector3(bbMax[0], bbMax[1], bbMin[2]), trans * btVector3(bbMax[0], bbMax[1], bbMax[2]), color);
	//drawLine(trans * btVector3(bbMin[0], bbMax[1], bbMin[2]), trans * btVector3(bbMin[0], bbMax[1], bbMax[2]), color);
	//drawLine(trans * btVector3(bbMin[0], bbMin[1], bbMax[2]), trans * btVector3(bbMax[0], bbMin[1], bbMax[2]), color);
	//drawLine(trans * btVector3(bbMax[0], bbMin[1], bbMax[2]), trans * btVector3(bbMax[0], bbMax[1], bbMax[2]), color);
	//drawLine(trans * btVector3(bbMax[0], bbMax[1], bbMax[2]), trans * btVector3(bbMin[0], bbMax[1], bbMax[2]), color);
	//drawLine(trans * btVector3(bbMin[0], bbMax[1], bbMax[2]), trans * btVector3(bbMin[0], bbMin[1], bbMax[2]), color);

}
*/

/*
void cPhysicsObject::RenderPlaneDebug (const btVector3& lbtPlaneNormal, btScalar lbtPlaneConst, const btTransform& lbtTransform, const btVector3& lbtColor)
{

	btVector3 lbtPlaneOrigin = lbtPlaneNormal * lbtPlaneConst;
	btVector3 lbtVec0, lbtVec1;
	btPlaneSpace1 (lbtPlaneNormal, lbtVec0, lbtVec1);
	btScalar lbtVecLen = 100.f;
	btVector3 lbtPt0 = lbtPlaneOrigin + lbtVec0 * lbtVecLen;
	btVector3 lbtPt1 = lbtPlaneOrigin - lbtVec0 * lbtVecLen;
	btVector3 lbtPt2 = lbtPlaneOrigin + lbtVec1 * lbtVecLen;
	btVector3 lbtPt3 = lbtPlaneOrigin - lbtVec1 * lbtVecLen;

	btVector3 lbt01 = lbtTransform * lbtPt0;
	btVector3 lbt02 = lbtTransform * lbtPt1;
	btVector3 lbt03 = lbtTransform * lbtPt2;
	btVector3 lbt04 = lbtTransform * lbtPt3;

	cVec3 lColor (lbtColor.getX(), lbtColor.getY(), lbtColor.getZ());

	cGraphicManager::Get().DrawLine(cVec3 (lbt01.getX(), lbt01.getY(), lbt01.getZ()), cVec3 (lbt02.getX(), lbt02.getY(), lbt02.getZ()), lColor);
	cGraphicManager::Get().DrawLine(cVec3 (lbt03.getX(), lbt03.getY(), lbt03.getZ()), cVec3 (lbt04.getX(), lbt04.getY(), lbt04.getZ()), lColor);

	
	
	//btVector3 planeOrigin = planeNormal * planeConst;
	//btVector3 vec0,vec1;
	//btPlaneSpace1(planeNormal,vec0,vec1);
	//btScalar vecLen = 100.f;
	//btVector3 pt0 = planeOrigin + vec0*vecLen;
	//btVector3 pt1 = planeOrigin - vec0*vecLen;
	//btVector3 pt2 = planeOrigin + vec1*vecLen;
	//btVector3 pt3 = planeOrigin - vec1*vecLen;
	//drawLine(transform*pt0,transform*pt1,color);
	//drawLine(transform*pt2,transform*pt3,color);

}
*/




//Obtenemos la posicion central del objeto
cVec3 cPhysicsObject::GetPosition ()
{
	cVec3 lPosition;

	btTransform lbtTransform;
	mpbtRigidBody->getMotionState()->getWorldTransform(lbtTransform);

	lPosition.x = lbtTransform.getOrigin().getX();
	lPosition.y = lbtTransform.getOrigin().getY();
	lPosition.z = lbtTransform.getOrigin().getZ();

	return lPosition;
}


//Establecememos la posicion central del objeto
void cPhysicsObject::SetPosition(const cVec3 &lvPosition)
{
	btTransform lbtTransform;

    mpbtRigidBody->getMotionState()->getWorldTransform(lbtTransform);
	lbtTransform.setOrigin(btVector3 (lvPosition.x, lvPosition.y, lvPosition.z));
    mpbtRigidBody->setWorldTransform(lbtTransform);
}




cQuaternion cPhysicsObject::GetQuatRotation()
{
	btTransform lbtTransform;
	mpbtRigidBody->getMotionState()->getWorldTransform(lbtTransform);
	btQuaternion lbtQ = lbtTransform.getRotation();

	return cQuaternion(lbtQ.getX(), lbtQ.getY(), lbtQ.getZ(), lbtQ.getW());
}



void cPhysicsObject::SetQuatRotation(const cQuaternion &lRotQuat)
{
    btTransform lbtTransform;  
    btQuaternion lbtRotQuat = btQuaternion(lRotQuat.x, lRotQuat.y, lRotQuat.z, lRotQuat.w);

	mpbtRigidBody->getMotionState()->getWorldTransform(lbtTransform);
    lbtTransform.setRotation(lbtRotQuat);
    mpbtRigidBody->setWorldTransform(lbtTransform);
}


cVec3 cPhysicsObject::GetAngSpeed()
{
    btVector3 btVec3 = mpbtRigidBody->getAngularVelocity();  
    return cVec3(btVec3.getX() , btVec3.getY(), btVec3.getZ());
}


float cPhysicsObject::GetSpeed()
{
    return mpbtRigidBody->getLinearVelocity().length();
}


cVec3 cPhysicsObject::GetLinearSpeed()
{
    btVector3 btVec3 = mpbtRigidBody->getLinearVelocity();
    return cVec3(btVec3.getX() , btVec3.getY(), btVec3.getZ());
}


//con esto le damos la vuelta al eje que viene en max que es ZUP
btQuaternion cPhysicsObject::CambiarEje(const cQuaternion &lRotQuat)
{

	btQuaternion lbtRotQuat = btQuaternion(lRotQuat.x, lRotQuat.y, lRotQuat.z, lRotQuat.w);

	btMatrix3x3 lbtMatrix = btMatrix3x3(1,0,0, 0,1,0, 0,0,1);  //Identidad, no se is pasarán otra, es al principio solo
	btTransform lbtTransform = btTransform(lbtMatrix);
	//lbtTransform.setRotation(btQuaternion(btVector3(1,0,0), -3.14159f / 2.0f));  //ASÍ FUNCIONA 
	//lbtTransform.setRotation(lbtRotQuat);  //NO VA, SEGURO PORQUE NO ENTIENDO LOS ANGULOS, NO SE PUEDE PASAR ASI DE FACIL
	lbtTransform.setRotation(btQuaternion(btVector3(lRotQuat.x,lRotQuat.y,lRotQuat.z), lRotQuat.w));  //ASÍ FUNCIONA 
	btQuaternion lbtQuaternion = lbtTransform.getRotation();

	return lbtQuaternion;
}

//Ya esta no la usamos
bool cPhysicsObject::CreateBoxShape(cVec3 lVec3)
{
	//btCollisionShape* lpbtShape;

	if ((lVec3.x > 0) && (lVec3.y > 0) && (lVec3.z > 0))
	{
		mpbtShape = new btBoxShape(btVector3(lVec3.x, lVec3.y, lVec3.z));  
		//lpbtShape = new btBoxShape(btVector3(lVec3.x, lVec3.y, lVec3.z));  
		//mabtCollisionShapes.push_back(lpbtShape);
	}
	else
		return false;
	
	//Intentar girar el shape
	

	return true;
}

btRigidBody* cPhysicsObject::LocalCreateRigidBody(float lfMass, const btTransform& lbtStartTransform, btCollisionShape* lbtShape)
{
	btAssert((!lbtShape || lbtShape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool lbIsDynamic = (lfMass != 0.f);

	btVector3 lbtLocalInertia(0, 0, 0);
	if (lbIsDynamic)
		lbtShape->calculateLocalInertia(lfMass, lbtLocalInertia);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

#define USE_MOTIONSTATE 1
#ifdef USE_MOTIONSTATE
	btDefaultMotionState* lbtMyMotionState = new btDefaultMotionState(lbtStartTransform);

	btRigidBody::btRigidBodyConstructionInfo cInfo(lfMass, lbtMyMotionState, lbtShape, lbtLocalInertia);

	btRigidBody* lbtBody = new btRigidBody(cInfo);
	//lbtBody->setContactProcessingThreshold(m_defaultContactProcessingThreshold);  //No se muy bien que hace esta línea, pero sin esto no colisiona

#else
	btRigidBody* body = new btRigidBody(mass,0,shape,localInertia);	
	body->setWorldTransform(startTransform);
#endif//

	//m_dynamicsWorld->addRigidBody(body);
	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	//btDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	//lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld->addRigidBody(lbtBody);


	return lbtBody;
}


/*
void cPhysiscsObject:RenderAllObjectDebug ()
{
}
*/

/*

//Intentado eliminar esta funcion para poner la otra de abajo
void cPhysicsObject::RenderObjectDebug()
{
	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);

	btTransform lbtTransform; 
	mpbtRigidBody->getMotionState()->getWorldTransform(lbtTransform); 

	//Pintando los ejes de coordenadas
	RenderTransformDebug(lbtTransform, 1.0);

	
	//Dibujando un cubo, sacado de btCollisionWorld.cpp 1217 (despues de mucho buscar y seguir codigo ...)
	btCollisionShape* lbtShape = mpbtRigidBody->getCollisionShape();
	const btBoxShape* lbtBoxShape = static_cast<const btBoxShape*>(lbtShape);
	btVector3 lbtHalfExtents = lbtBoxShape->getHalfExtentsWithMargin();
	btVector3 lbtColor(1.0f, 0.0f, 0.0f); //si se pasa por parametro a lo mejor podemos dibujar cosas de muchos colores
	RenderBoxDebug(- lbtHalfExtents, lbtHalfExtents, lbtTransform, lbtColor);
}
*/


/*
void cPhysicsObject::LocalCreateSphereRigidBody(float lfRadio, cVec3 lPosition)
{

	
}
*/