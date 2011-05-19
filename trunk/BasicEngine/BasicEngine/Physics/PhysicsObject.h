/*
clase 
	Representa un fisica de un objeto determinado
*/

#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

class cPhysicsObject {

public:
	virtual void Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Deinit(void) = 0;
};

#endif