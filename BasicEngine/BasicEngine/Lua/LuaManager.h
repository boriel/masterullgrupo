/*
Class LuaManager: Sacado de los ejemplo de IA de Sonia

*/

#ifndef LUAMANAGER_H
#define LUAMANAGER_H

#include <string>

#include "..\Utility\Singleton.h"


// extern C le dice al compilador que la libreria debe ser compilada en C y no en C++
extern "C"
{
	#include "src/lua.h"
	#include "src/lauxlib.h"
	#include "src/lualib.h"
}







class cLuaManager : public cSingleton<cLuaManager>
{
	public:
		void Init();
		void Deinit();
		
		bool DoString( const char *lacStatement );
		bool DoFile( const char* lacFile );
		void Register( const char* lacFuncName, lua_CFunction lpFunc );

		inline lua_State* GetContext() { return mpLuaContext; }



		
		void PushArg( int liArg );
		void PushArg( long liArg );
		void PushArg( float lfArg );
		void PushArg( const char* lacArg );
		void PushArg( std::string &lacArg );
		void PushArg( bool lbArg );
		

		void GetRetValue( int* liRet );
		void GetRetValue( float* lfRet );
		void GetRetValue( long* liRet );
		void GetRetValue( std::string* lacRet );
		void GetRetValue( const char* lacRet );
		void GetRetValue( bool* lbRet );


		void Pop( unsigned int luiNValues );



		template <class T, class U, class Z>
		bool CallLua( const char* lacFuncName, T lArg1, U lArg2, Z* lpRet);



		friend class cSingleton<cLuaManager>;
		

	protected:
		cLuaManager(); // Protected constructor
		private:
		lua_State* mpLuaContext;
		
	private:	
		bool cLuaManager::CheckError( int liError );


};



template <class T, class U, class Z>
bool cLuaManager::CallLua( const char* lacFuncName, T lArg1, U lArg2, Z* lpRet)
{
	assert( mpLuaContext );
	
	//Introducimos en la pila el nombre de la funcion
	//definida en Lua que queremos llamar
	lua_getglobal( mpLuaContext, lacFuncName );
	
	//Chequeamos que la funci�n esta definida en Lua
	int lbExists = lua_isfunction( mpLuaContext, -1 );
	
	//Si no esta definida en Lua
	if ( !lbExists )
	{
		//Sacamos el nombre de la funci�n de la pila de Lua
		Pop( 1 );
		printf( "Error: la funcion %s no existe\n", lacFuncName );
		return false;
	}

	//Si la funci�n esta definida en Lua...
	//Introducimos en la pila el primer argumento
	PushArg( lArg1 );
	
	//Introducimos en la pila el segundo argumento
	PushArg( lArg2 );
	
	//La funcion devuelve un valor
	if ( lpRet )
	{
		//Llamamos a la funcion
		lua_call( mpLuaContext, 2, 1 );
		//Obtenemos el resultado
		GetRetValue( lpRet );
		//Eliminamos el valor de retorno de la pila
		Pop( 1 );
	}
	//La funci�n no devuelve ningun valor
	else
	{
		//Llamamos a la funci�n
		lua_call( mpLuaContext, 2, 0 );
	}
	return true;
}




#endif