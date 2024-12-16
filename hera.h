#pragma once

#define CLIENT_DLL
#define WIN32_LEAN_AND_MEAN
#define GAME_DLL true

#include "GMLuaModule.h"

namespace hera
{
	int init( lua_State* L );
	int unload( lua_State* L );
};