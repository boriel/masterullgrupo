#include "PhysicsObject.h"


//#include "btBulletDynamicsCommon.h" 
#include "..\Graphics\GraphicManager.h"

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

/*
	drawLine(trans * btVector3(bbMin[0], bbMin[1], bbMin[2]), trans * btVector3(bbMax[0], bbMin[1], bbMin[2]), color);
	drawLine(trans * btVector3(bbMax[0], bbMin[1], bbMin[2]), trans * btVector3(bbMax[0], bbMax[1], bbMin[2]), color);
	drawLine(trans * btVector3(bbMax[0], bbMax[1], bbMin[2]), trans * btVector3(bbMin[0], bbMax[1], bbMin[2]), color);
	drawLine(trans * btVector3(bbMin[0], bbMax[1], bbMin[2]), trans * btVector3(bbMin[0], bbMin[1], bbMin[2]), color);
	drawLine(trans * btVector3(bbMin[0], bbMin[1], bbMin[2]), trans * btVector3(bbMin[0], bbMin[1], bbMax[2]), color);
	drawLine(trans * btVector3(bbMax[0], bbMin[1], bbMin[2]), trans * btVector3(bbMax[0], bbMin[1], bbMax[2]), color);
	drawLine(trans * btVector3(bbMax[0], bbMax[1], bbMin[2]), trans * btVector3(bbMax[0], bbMax[1], bbMax[2]), color);
	drawLine(trans * btVector3(bbMin[0], bbMax[1], bbMin[2]), trans * btVector3(bbMin[0], bbMax[1], bbMax[2]), color);
	drawLine(trans * btVector3(bbMin[0], bbMin[1], bbMax[2]), trans * btVector3(bbMax[0], bbMin[1], bbMax[2]), color);
	drawLine(trans * btVector3(bbMax[0], bbMin[1], bbMax[2]), trans * btVector3(bbMax[0], bbMax[1], bbMax[2]), color);
	drawLine(trans * btVector3(bbMax[0], bbMax[1], bbMax[2]), trans * btVector3(bbMin[0], bbMax[1], bbMax[2]), color);
	drawLine(trans * btVector3(bbMin[0], bbMax[1], bbMax[2]), trans * btVector3(bbMin[0], bbMin[1], bbMax[2]), color);
*/
}



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

	
	/*
	btVector3 planeOrigin = planeNormal * planeConst;
	btVector3 vec0,vec1;
	btPlaneSpace1(planeNormal,vec0,vec1);
	btScalar vecLen = 100.f;
	btVector3 pt0 = planeOrigin + vec0*vecLen;
	btVector3 pt1 = planeOrigin - vec0*vecLen;
	btVector3 pt2 = planeOrigin + vec1*vecLen;
	btVector3 pt3 = planeOrigin - vec1*vecLen;
	drawLine(transform*pt0,transform*pt1,color);
	drawLine(transform*pt2,transform*pt3,color);
*/
}


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



cQuaternion cPhysicsObject::GetQuatRotation()
{
	//cVec3 lVecRotation;
	cQuaternion lQuatRotation;

	btTransform lbtTransform;
	mpbtRigidBody->getMotionState()->getWorldTransform(lbtTransform);

	btQuaternion lbtQuaternion =  lbtTransform.getRotation();
	
	lQuatRotation.x = lbtQuaternion.getX();
	lQuatRotation.y = lbtQuaternion.getY();
	lQuatRotation.z = lbtQuaternion.getZ();
	lQuatRotation.w = lbtQuaternion.getW();


	return lQuatRotation;
}

