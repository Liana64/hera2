#include <string>

#include "hera.h"
#include "CStateManager.h";
#include "CAutoUnRef.h"
#include "vfnhook.h"

#include "icvar.h"
#include "convar.h"

//#include "statemanager.h"

ILuaInterface* lua;
ILuaInterface* c = CStateManager::GetInterface( LuaStates::CLIENT );
ILuaInterface* s = CStateManager::GetInterface( LuaStates::SERVER );
ILuaInterface* m = CStateManager::GetInterface( LuaStates::MENU );

ICvar *hcvar = NULL;

void states( const CCommand &args )
{
	lua->Msg( "] menu state at 0x%p\n", m );
	lua->Msg( "] client state at 0x%p\n", c );
	lua->Msg( "] server state at 0x%p\n", s );
}
ConCommand h_states("h_states", states, "Check heras states", 0);

void RunStringM( const CCommand &args )
{
	lua->RunString( "cl_init.lua", "gamemodes\\base\\gamemode\\cl_init.lua", args.ArgS( ), true, true );
}
ConCommand h_run("h_run", RunStringM, "Run Lua in the menu state", 0);

void RunStringC( const CCommand &args )
{
	c->RunString( "cl_init.lua", "gamemodes\\base\\gamemode\\cl_init.lua", args.ArgS( ), true, true );
}
ConCommand h_run_c("h_run_c", RunStringM, "Run Lua in the client state", 0);

void update( const CCommand &args )
{
	c = CStateManager::GetInterface( LuaStates::CLIENT );
	lua->Msg( "] saved client state to 0x%p\n", c );
	s = CStateManager::GetInterface( LuaStates::SERVER );
	lua->Msg( "] saved server state to 0x%p\n", s );
}
ConCommand h_update("h_refresh", update, "Refresh states", 0);

LUA_FUNCTION(cvar_get)
{
	lua->CheckType(1, GLua::TYPE_STRING);
	if ( !hcvar->FindVar( lua->GetString( 1 ) ) )
	{
		lua->Error( "] convar doesn't exist..." );
		return 0;
	}
	
	lua->Push( hcvar->FindVar( lua->GetString( 1 ) ) );
	return 1;
}


int hera::init( lua_State *L ) {
	lua = Lua( );

	lua->Msg( "\n"
			" _                    ____  \n"
			"| |__   ___ _ __ __ _|___ \ \n"
			"| '_ \ / _ \ '__/ _` | __) |\n"
			"| | | |  __/ | | (_| |/ __/ \n"
			"|_| |_|\___|_|  \__,_|_____|\n" );
                            
	lua->Msg( "] initializing hera2...\n" );

	HMODULE client = LoadLibrary( "client.dll" );
	hcvar = *(ICvar **)GetProcAddress(client, "cvar");
	//hera::g_StateManager->SetMenuState(L);
	//hera::g_StateManager->SetActiveState(L);
	lua->Msg( "] found menu state at 0x%p...\n", m );

	/*lua->NewGlobalTable( "hcvar" );
	CAutoUnRef hcvar = lua->GetGlobal( "hcvar" );
		hcvar->SetMember( "get", cvar_get );
	*/
	
	hcvar->RegisterConCommand( &h_run );
	hcvar->RegisterConCommand( &h_run_c );
	hcvar->RegisterConCommand( &h_states );
	hcvar->RegisterConCommand( &h_update );
	
	lua->NewGlobalTable( "hera" );
	CAutoUnRef hera = lua->GetGlobal( "hera" );
		//hera->SetMember( "cvar", lua->GetGlobal( "hcvar" ) );
	
	return 0;
}

int hera::unload( lua_State *L ) {
	lua->Msg( "] unloading hera2...\n" );
	hcvar->UnregisterConCommand( &h_run );
	hcvar->UnregisterConCommand( &h_run_c );
	hcvar->UnregisterConCommand( &h_states );
	hcvar->UnregisterConCommand( &h_update );

	return 0;
}