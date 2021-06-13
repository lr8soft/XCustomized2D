#pragma once
#ifndef _LUA_UTIL_H_
#define _LUA_UTIL_H_
#include "../ThirdParty/lua/lua.hpp"
#include "LogUtil.hpp"
#include <string>
#include <any>
#include <vector>
#include <map>
class LuaUtil {
public:
	static lua_State* CreateNewEvon();
	static void ReleaseEvon(lua_State* pState);

	static bool LoadLuaFile(lua_State* pState, const std::string& scriptName);

	static bool InvokeLuaFunction(lua_State* pState, const std::string& functionName, size_t returnCount, std::initializer_list<std::any> paraments,
		bool isGlobalFunction = true, const std::string& parentModuleName = "");


	static std::vector<int> ParseLuaIntegerTable(lua_State* pState, int index);
	static std::vector<float> ParseLuaFloatTable(lua_State* pState, int index);
	static std::vector<std::string> ParseLuaStringTable(lua_State* pState, int index);

	static std::map<std::string, std::any> ParseMapLikeTable(lua_State* pState, int index);

	static std::any ParseValue(lua_State* pState, int index);
	
	template<typename T>
	inline static T ParseIndexValue(lua_State* pState, int index)
	{
		if (std::is_same<bool, T>::value)
		{
			bool value;
			value = std::any_cast<int>(ParseValue(pState, index));

			return value;
		}
		else if (std::is_same<int, T>::value || std::is_same<float, T>::value || std::is_same<double, T>::value ||
			std::is_same<unsigned int, T>::value || std::is_same<unsigned short, T>::value || std::is_same<short, T>::value)
		{
			return std::any_cast<lua_Number>(ParseValue(pState, index));
		}
		else {
			return std::any_cast<T>(ParseValue(pState, index));
		}

	}

};

#endif


