#pragma once
#ifndef _ENGINE_MAPPER_H_
#define _ENGINE_MAPPER_H_
#include "../Util/LuaUtil.h"

#define ENGINE_MAPPER_NAMESPACE "XCustomized2D.Engine"

class EngineMapper {

private:
	static int LuaGetScreenSize(lua_State* lua);
public:

	static int InitEngineLibs(lua_State* lua);
};

#endif