#include "hera.h"
GMOD_MODULE(init, unload);

int init( lua_State* L )
{
	return hera::init(L);
}

int unload( lua_State* L )
{
	return hera::unload(L);
}