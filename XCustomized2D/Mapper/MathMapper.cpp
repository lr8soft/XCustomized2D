#include "MathMapper.h"
#include "../Util/LuaUtil.h"
#include "../Util/LogUtil.hpp"

#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4** MathMapper::GetMatrix(lua_State * luaState)
{
	glm::mat4 **object = (glm::mat4**)luaL_checkudata(luaState, 1, MATH_HELPER_NAMESPACE);
	luaL_argcheck(luaState, object != NULL, 1, "invalid Matrix data");


	return object;
}

int MathMapper::LuaShowMatrix(lua_State * luaState)
{
	glm::mat4 **object = GetMatrix(luaState);

	std::string info;

	for (int i = 0; i < 4; i++)
	{
		info += std::to_string((**object)[i].x) + " " + std::to_string((**object)[i].y) + " " + std::to_string((**object)[i].z) + " " + std::to_string((**object)[i].w) + '\n';
	}
	
	LogUtil::printInfo("Show Matrix:\n" + info);
	return 0;
}

int MathMapper::LuaScaleMatrix(lua_State * luaState)
{
	glm::mat4 **object = GetMatrix(luaState);

	auto scaleValue = LuaUtil::ParseLuaFloatTable(luaState, -1);
	glm::vec3 scaleAxis = glm::vec3(scaleValue[0], scaleValue[1], scaleValue[2]);


	**object = glm::scale(**object, scaleAxis);	

	return 0;
}

int MathMapper::LuaRotateMatrix(lua_State * luaState)
{
	glm::mat4 **object = GetMatrix(luaState);

	auto rotateValue = LuaUtil::ParseLuaIntegerTable(luaState, -1);
	glm::vec3 rotateAxis = glm::vec3(rotateValue[0], rotateValue[1], rotateValue[2]);

	luaL_checktype(luaState, -2, LUA_TNUMBER);
	float angle = lua_tonumber(luaState, -2);

	**object = glm::rotate(**object, glm::radians(angle), rotateAxis);

	return 0;
}

int MathMapper::LuaTranslateMatrix(lua_State * luaState)
{
	glm::mat4 **object = GetMatrix(luaState);

	auto translateValue = LuaUtil::ParseLuaFloatTable(luaState, -1);

	glm::vec3 translateVector = glm::vec3(translateValue[0], translateValue[1], translateValue[2]);

	**object = glm::translate(**object, translateVector);

	return 0;
}

int MathMapper::LuaCreateMatrix(lua_State * luaState)
{

	glm::mat4 **s = (glm::mat4**)lua_newuserdata(luaState, sizeof(glm::mat4*));
	*s = new glm::mat4();

	luaL_getmetatable(luaState, MATH_HELPER_NAMESPACE);
	lua_setmetatable(luaState, -2);

	return 1;
}

int MathMapper::LuaCreateViewMatrix(lua_State * luaState)
{
	int stackIndex = -1;

	auto up = LuaUtil::ParseLuaFloatTable(luaState, stackIndex--);
	auto center = LuaUtil::ParseLuaFloatTable(luaState, stackIndex--);
	auto eye = LuaUtil::ParseLuaFloatTable(luaState, stackIndex--);

	glm::mat4 **s = (glm::mat4**)lua_newuserdata(luaState, sizeof(glm::mat4*));
	*s = new glm::mat4();
	**s = glm::lookAt(glm::vec3(eye[0], eye[1], eye[2]), glm::vec3(center[0], center[1], center[2]), glm::vec3(up[0], up[1], up[2] ));


	luaL_getmetatable(luaState, MATH_HELPER_NAMESPACE);
	lua_setmetatable(luaState, -2);

	return 1;
}

int MathMapper::LuaCreateProjectionMatrix(lua_State * luaState)
{

	int stackIndex = -1;

	float farDist = LuaUtil::ParseIndexValue<float>(luaState, stackIndex--);

	float nearDist = LuaUtil::ParseIndexValue<float>(luaState, stackIndex--);

	float aspect = LuaUtil::ParseIndexValue<float>(luaState, stackIndex--);
	float zoom = LuaUtil::ParseIndexValue<float>(luaState, stackIndex--);


	glm::mat4 **s = (glm::mat4**)lua_newuserdata(luaState, sizeof(glm::mat4*));
	*s = new glm::mat4();
	**s = glm::perspective(glm::radians(zoom), aspect, nearDist, farDist);
	

	luaL_getmetatable(luaState, MATH_HELPER_NAMESPACE);
	lua_setmetatable(luaState, -2);

	return 1;
}

int MathMapper::LuaDeleteMatrix(lua_State * luaState)
{
	glm::mat4 **object = (glm::mat4**)lua_touserdata(luaState, 1);
	if (object)
	{
		delete *object;
		*object = nullptr;
	}


	return 0;
}

glm::mat4 * MathMapper::ConvertToMatrix(lua_State * luaState, int index)
{
	glm::mat4 **object = (glm::mat4**)luaL_checkudata(luaState, index, MATH_HELPER_NAMESPACE);
	luaL_argcheck(luaState, object != NULL, 1, "invalid Matrix data");
	return *object;
}

int MathMapper::InitMatrixFuncLibs(lua_State * luaState)
{
	luaL_newmetatable(luaState, MATH_HELPER_NAMESPACE);
	/* metatable.__index = metatable */
	lua_pushvalue(luaState, -1);  /* duplicates the metatable */
	lua_setfield(luaState, -2, "__index");


	static const struct luaL_Reg objectlib_m[] = {
		{"Rotate", LuaRotateMatrix},
		{"Scale", LuaScaleMatrix},
		{"Translate", LuaTranslateMatrix},
		{"Show", LuaShowMatrix},
		{"__gc", LuaDeleteMatrix},
		{NULL, NULL}
	};

	static const struct luaL_Reg objectlib_f[] = {
		{"CreateMatrix", LuaCreateMatrix},
		{"CreateProjectionMatrix", LuaCreateProjectionMatrix},
		{"CreateViewMatrix", LuaCreateViewMatrix},
		{NULL, NULL}
	};

	luaL_setfuncs(luaState, objectlib_m, 0);
	luaL_newlib(luaState, objectlib_f);

	return 1;
}
