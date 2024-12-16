#pragma once

#include "hera.h"

class StateManager
{
public:
	StateManager() {};
	~StateManager() {};

	inline void SetActiveState( lua_State* L ) { _stateActive = L; };
	//inline void SetMenuState( lua_State* L ) { _stateMenu = hera::m; };
	//inline void SetGameState( lua_State* L ) { _stateGame = hera::c; };

	inline lua_State* GetActiveState() { return _stateActive; };
	inline lua_State* GetMenuState() { return _stateMenu; };
	inline lua_State* GetGameState() { return _stateGame; };

private:
	lua_State *_stateActive, *_stateMenu, *_stateGame;
};

namespace hera
{
	static StateManager *g_StateManager = new StateManager();
}