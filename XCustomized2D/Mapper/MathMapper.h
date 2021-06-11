#pragma once
#ifndef _MATH_MAPPER_H_
#define _MATH_MAPPER_H_
#include "../Util/LuaUtil.h"
#include <glm/glm.hpp>


#define MATH_HELPER_NAMESPACE "XCustomized2D.MathHelper"



class MathMapper {
private:
	static glm::mat4** GetMatrix(lua_State * luaState);

	static int LuaShowMatrix(lua_State* luaState);

	static int LuaScaleMatrix(lua_State* luaState);
	static int LuaRotateMatrix(lua_State* luaState);
	static int LuaTranslateMatrix(lua_State* luaState);

	static int LuaCreateMatrix(lua_State* luaState);
	static int LuaDeleteMatrix(lua_State* luaState);
public:
	static glm::mat4* ConvertToMatrix(lua_State* luaState, int index);

	static int InitMathFuncLibs(lua_State * luaState);
	

};


#endif