#include "LuaUtil.h"
#include "LogUtil.hpp"
#include "../EngineDefine.h"
#include <string>

using namespace std;

lua_State* LuaUtil::CreateNewEvon()
{
	lua_State* luaState = luaL_newstate();
	static const luaL_Reg lualibs[] = {
		{ "base", luaopen_base },
		{ "math", luaopen_math },
		{ "io", luaopen_io },
		{ "os", luaopen_os },
	    { "string", luaopen_string },
		{ "package", luaopen_package },
		{ NULL, NULL}
	};

	const luaL_Reg *lib = lualibs;
	for (; lib->func != nullptr; lib++)
	{
		luaL_requiref(luaState, lib->name, lib->func, 1);
		lua_pop(luaState, 1);
	}
	return luaState;
}

void LuaUtil::ReleaseEvon(lua_State* pState)
{
	lua_close(pState);
}

bool LuaUtil::LoadLuaFile(lua_State * pState, const std::string & scriptName)
{
	int status = luaL_loadfile(pState, (DEFAULT_SCRIPT_FOLDEER + scriptName).c_str());
	if (status == LUA_OK)
	{
		lua_pcall(pState, 0, LUA_MULTRET, 0);//call default lua function

		return true;
	}
	return false;

}

bool LuaUtil::InvokeLuaFunction(lua_State * pState, const std::string & functionName, size_t returnCount,
	std::initializer_list<std::any> paraments, bool isGlobalFunction, const std::string& parentModuleName)
{
	if (isGlobalFunction)
	{
		lua_getglobal(pState, functionName.c_str());
	}
	else {
		lua_getglobal(pState, parentModuleName.c_str());
		lua_getfield(pState, -1, functionName.c_str());	//push function to the top of the stack
	}


	for (std::any para : paraments)	//parse all  parameter
	{
		string paraType = para.type().name();
		if (paraType == "int")
		{
			int value = any_cast<int>(para);
			lua_pushnumber(pState, value);
		}
		else if (paraType == "float")
		{
			float value = any_cast<float>(para);
			lua_pushnumber(pState, value);
		}
		else if (paraType == "double")
		{
			double value = any_cast<double>(para);
			lua_pushnumber(pState, value);
		}
		else if (paraType == "string")
		{
			string value = any_cast<string>(para);
			lua_pushstring(pState, value.c_str());
		}
		else if (paraType == "char")
		{
			char realValue[2];
			realValue[0] = any_cast<char>(para);
			realValue[0] = '\0';
			lua_pushstring(pState, realValue);
		}
		else if (paraType.find("char const") != paraType.npos)
		{
			const char* value = any_cast<char const*>(para);
			lua_pushstring(pState, value);
		}
	}

	int result = lua_pcall(pState, paraments.size(), returnCount, 0);//call the function, 0 parameter 0 return
	if (result)
	{
		return false;
	}
	return true;
}

std::vector<int> LuaUtil::ParseLuaIntegerTable(lua_State * pState, int index)
{
	luaL_checktype(pState, index, LUA_TTABLE);

	std::vector<int> value;

	size_t elementSizeLength = luaL_len(pState, index);


	for (int i = 1; i <= elementSizeLength; ++i) {
		lua_rawgeti(pState, index, i);	//set the element to top

		int v = lua_tointeger(pState, -1);	//read the top of stack
		value.push_back(v);

		lua_pop(pState, 1);	//pop the top of the stack
	}


	return value;
}

std::vector<float> LuaUtil::ParseLuaFloatTable(lua_State * pState, int index)
{
	luaL_checktype(pState, index, LUA_TTABLE);

	std::vector<float> value;

	size_t elementSizeLength = luaL_len(pState, index);

	for (int i = 1; i <= elementSizeLength; ++i) {
		lua_rawgeti(pState, index, i);

		float v = lua_tonumber(pState, -1);
		value.push_back(v);

		lua_pop(pState, 1);	
	}


	return value;
}



/*
	lua_State* luaState = LuaUtil::getNewGameObjectEvon();

	int status = luaL_loadfile(luaState, "assets/Script/test.lua");
	{//call add(1, 233.0)
		lua_pcall(luaState, 0, LUA_MULTRET, 0);

		lua_getglobal(luaState, "add");
		lua_pushnumber(luaState, 1);
		lua_pushnumber(luaState, 233.0);

		lua_call(luaState, 2, 1);//2 parameter, 1 return
		float sum = lua_tonumber(luaState, -1);// get return from -1 (top of stack)
		lua_pop(luaState, 1);//pop the return value

		LogUtil::printInfo(std::to_string(sum));
	}
	{//globalTestValue = "LT_lrsoft"
		lua_pushstring(luaState, "LT_lrsoft");
		lua_setglobal(luaState, "globalTestValue");
	}
	{//read from globalTestValue
		lua_getglobal(luaState, "globalTestValue");
		string str = lua_tostring(luaState, -1);
		lua_pop(luaState, 1);
		LogUtil::printInfo(str);
	}
	{//send luatable to lua file
		lua_createtable(luaState, 2, 0);
		lua_pushnumber(luaState, 1);
		lua_pushnumber(luaState, 233);

		lua_rawset(luaState, -3);
		lua_pushnumber(luaState, 2);
		lua_pushstring(luaState, "testtesttest");

		lua_rawset(luaState, -3);
		lua_pushnumber(luaState, 3);
		lua_pushstring(luaState, "lualualua");

		lua_rawset(luaState, -3);
		lua_pushnumber(luaState, 3);
		lua_pushstring(luaState, "aaaaaa");

		lua_rawset(luaState, -3);
		lua_setglobal(luaState, "arg");
		luaL_dofile(luaState, "assets/Script/test.lua");
	}
	{//get multi-return from lua
		lua_pcall(luaState, 0, LUA_MULTRET, 0);
		lua_getglobal(luaState, "getValue");
		lua_call(luaState, 0, 3);

		while(lua_gettop(luaState))
		{
			switch (lua_type(luaState, lua_gettop(luaState)))
			{
			case LUA_TNUMBER:
				LogUtil::printInfo(std::to_string(lua_tonumber(luaState, lua_gettop(luaState)))); break;
			case LUA_TTABLE:
				LogUtil::printInfo("TYPE TABLE"); break;
			case LUA_TSTRING:
				LogUtil::printInfo(lua_tostring(luaState, lua_gettop(luaState))); break;
			case LUA_TBOOLEAN:
				LogUtil::printInfo(std::to_string(lua_toboolean(luaState, lua_gettop(luaState)))); break;
			default:
				LogUtil::printError("Unknown return type");
			}
			lua_pop(luaState, 1);
		}

	}
*/