/*
clase 
	Representa un fisica de un objeto determinado
*/

#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include <string>

class cPhysicsObject {
public:
	virtual void Init( const std::string &lacNameID) = 0;
	virtual void Update(void) = 0;
	virtual void Deinit(void) = 0;

protected:
	std::string macNameID;
};

#endif