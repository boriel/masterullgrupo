/*
Clase Singleton.h:
	
	El singleton es uno de los patrones de diseño más simples y extendidos. Se utiliza para garantizar 
	que una clase sólo tenga una instancia y para proporcionar un acceso gloabal a ella.
	Este Singleton corresponde a Meyers

*/

#ifndef Singleton_H
#define Singleton_H


template <typename T> class cSingleton
{
	public:
		static T& Get()
		{
			static T lInstance;
			return lInstance;
		}
};

#endif