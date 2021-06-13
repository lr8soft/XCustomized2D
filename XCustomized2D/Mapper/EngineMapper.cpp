#include "EngineMapper.h"
#include "../FrameInfo.h"
#include "../Util/LuaUtil.h"
int EngineMapper::LuaGetScreenSize(lua_State * luaState)
{
	lua_settop(luaState, 0);
	lua_pushnumber(luaState, FrameInfo::ScreenWidth);
	lua_pushnumber(luaState, FrameInfo::ScreenHeight);

	return 2;
}

int EngineMapper::InitEngineLibs(lua_State* luaState)
{
	luaL_newmetatable(luaState, ENGINE_MAPPER_NAMESPACE);
	/* metatable.__index = metatable */
	lua_pushvalue(luaState, -1);  /* duplicates the metatable */
	lua_setfield(luaState, -2, "__index");


	static const struct luaL_Reg objectlib_m[] = {
	/*	{"Rotate", LuaRotateMatrix},
		{"Scale", LuaScaleMatrix},
		{"Translate", LuaTranslateMatrix},
		{"Show", LuaShowMatrix},
		{"__gc", LuaDeleteMatrix},*/
		{NULL, NULL}
	};

	static const struct luaL_Reg objectlib_f[] = {
		{"GetScreenSize", LuaGetScreenSize },

		{NULL, NULL}
	};

	luaL_setfuncs(luaState, objectlib_m, 0);
	luaL_newlib(luaState, objectlib_f);

	return 1;
}
