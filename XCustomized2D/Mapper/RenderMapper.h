#pragma once
#ifndef _RENDER_MAPPER_H_
#define _RENDER_MAPPER_H_

#define RENDER_HELPER_NAMESPACE "XCustomized2D.RenderHelper"
#include "../Util/LuaUtil.h"

#include <map>
#include <string>
#include <any>
class RenderMapper {
private:
	static	std::map<std::string, std::any> ParseUniformData(lua_State* luaState, int index);
public:

	static int LuaCreateRenderBatch(lua_State * luaState);
	static int LuaRenderBatch(lua_State * luaState);


	static int InitRenderFuncLibs(lua_State * luaState);


};

#endif