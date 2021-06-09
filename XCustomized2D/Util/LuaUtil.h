#pragma once
#ifndef _LUA_UTIL_H_
#define _LUA_UTIL_H_
#include "../ThirdParty/lua/lua.hpp"
#include <string>
#include <any>
class LuaUtil {
public:
	static lua_State* CreateNewEvon();
	static void ReleaseEvon(lua_State* pState);

	static bool LoadLuaFile(lua_State* pState, const std::string& scriptName);

	static bool InvokeLuaFunction(lua_State* pState, const std::string& functionName, size_t returnCount, std::initializer_list<std::any> paraments,
		bool isGlobalFunction = true, const std::string& parentModuleName = "");

};

#endif