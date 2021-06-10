#pragma once
#ifndef _MATH_MAPPER_H_
#define _MATH_MAPPER_H_
#include "../Util/LuaUtil.h"
#include <glm/glm.hpp>


#define MATH_HELPER_NAMESPACE "XCustomized2D.MathHelper"



class MathMapper {
private:
	static glm::mat4** GetMatrix(lua_State * luaState);

	static int LuaShowMatrix4(lua_State* luaState);

	static int LuaScaleMatrix4(lua_State* luaState);
	static int LuaRotateMatrix4(lua_State* luaState);
	static int LuaTranslateMatrix4(lua_State* luaState);

	static int LuaCreateMatrix4(lua_State* luaState);
	static int LuaDeleteMatrix4(lua_State* luaState);
public:
	static int InitMathFuncLibs(lua_State * luaState);
	

};


#endif