#include "RenderMapper.h"
#include "../Util/LuaUtil.h"

#include "../Base/RenderEnum.h"
#include "../Base/RenderManager.h"

#include <GL3/gl3w.h>

#include "MathMapper.h"
#include <string>

using namespace std;

std::map<std::string, std::any> RenderMapper::ParseUniformData(lua_State * luaState, int index)
{
	return std::map<std::string, std::any>();
}

int RenderMapper::LuaUpdateBlendSetting(lua_State * luaState)
{
	int functionValue = LuaUtil::ParseIndexValue<int>(luaState, -1);
	int functionID = LuaUtil::ParseIndexValue<int>(luaState, -2);

	glBlendFunc(functionID, functionValue);

	return 0;
}

int RenderMapper::LuaUpdateRenderSetting(lua_State * luaState)
{
	bool enableFunction = LuaUtil::ParseIndexValue<bool>(luaState, -1);
	int functionID = LuaUtil::ParseIndexValue<int>(luaState, -2);

	if (enableFunction)
	{
		glEnable(functionID);
	}
	else {
		glDisable(functionID);
	}


	return 0;
}

int RenderMapper::LuaCreateRenderBatch(lua_State * luaState)
{
	int stackIndex = -1;

	luaL_checktype(luaState, stackIndex, LUA_TBOOLEAN);
	bool needNormalized = lua_toboolean(luaState, stackIndex--);


	std::vector<int> elementSize = LuaUtil::ParseLuaIntegerTable(luaState, stackIndex--);
	std::vector<int> elementLength = LuaUtil::ParseLuaIntegerTable(luaState, stackIndex--);
	std::vector<int> formats = LuaUtil::ParseLuaIntegerTable(luaState, stackIndex--);
	std::vector<float> vertices = LuaUtil::ParseLuaFloatTable(luaState, stackIndex--);
	std::vector<int> indices = LuaUtil::ParseLuaIntegerTable(luaState, stackIndex--);


	std::vector<void*> realFormat;
	for (int length : formats)
	{
		realFormat.push_back((void*)length);
	}

	//std::vector<>

	luaL_checktype(luaState, stackIndex, LUA_TSTRING);
	string strBufferUsage = lua_tostring(luaState, stackIndex);

	BufferUsage bufferUsage;

	if (strBufferUsage == "DYNAMIC_DRAW")
	{
		bufferUsage = DYNAMIC_DRAW;
	}
	else {
		bufferUsage = STATIC_DRAW;
	}

	std::string uuid = RenderManager::getInstance()->CreateBatch(bufferUsage, indices, vertices, realFormat, elementLength, elementSize, needNormalized);

	lua_settop(luaState, 0);
	lua_pushstring(luaState, uuid.c_str());
	

	return 1;
}

int RenderMapper::LuaRenderBatch(lua_State * luaState)
{
	int stackIndex = -1;
	std::vector<float> updateVertices = LuaUtil::ParseLuaFloatTable(luaState, stackIndex--);

	luaL_checktype(luaState, stackIndex, LUA_TNUMBER);
	int updateOffset = lua_tointeger(luaState, stackIndex--);

	luaL_checktype(luaState, stackIndex, LUA_TNUMBER);
	int indexSize = lua_tointeger(luaState, stackIndex--);

	//glm::mat4* matrix = MathMapper::ConvertToMatrix(luaState, stackIndex--);
	auto uniformData = LuaUtil::ParseMapLikeTable(luaState, stackIndex--);

	/***********get texture map*********/
	std::vector<std::string> imageInfo = LuaUtil::ParseLuaStringTable(luaState, stackIndex--);
	std::map<std::string, std::string> imageGroup;
	string textureMapperName;
	bool isImagePath = false;
	for (string info : imageInfo)
	{
		if (!isImagePath)
		{
			textureMapperName = info;
		}
		else {
			imageGroup[textureMapperName] = info;
		}
		isImagePath = !isImagePath;
	}
	/***********get texture map*********/

	luaL_checktype(luaState, stackIndex, LUA_TSTRING);
	string shaderName = lua_tostring(luaState, stackIndex--);

	luaL_checktype(luaState, stackIndex, LUA_TSTRING);
	string shaderFolderName = lua_tostring(luaState, stackIndex--);


	luaL_checktype(luaState, stackIndex, LUA_TSTRING);
	string uuid = lua_tostring(luaState, stackIndex--);

	size_t updateVerticesSize = updateVertices.size();
	if (updateVerticesSize > 0)
	{
		RenderManager::getInstance()->RenderBatch(uuid, shaderFolderName, shaderName, imageGroup, uniformData, indexSize, updateOffset, updateVerticesSize * sizeof(float), &updateVertices[0]);
	}
	else {
		RenderManager::getInstance()->RenderBatch(uuid, shaderFolderName, shaderName, imageGroup, uniformData, indexSize);
	}

	

	return 0;
}

int RenderMapper::InitRenderFuncLibs(lua_State * luaState)
{
	luaL_newmetatable(luaState, RENDER_HELPER_NAMESPACE);
	/* metatable.__index = metatable */
	lua_pushvalue(luaState, -1);  /* duplicates the metatable */
	lua_setfield(luaState, -2, "__index");


	static const struct luaL_Reg objectlib_m[] = {

	{NULL, NULL}
	};

	static const struct luaL_Reg objectlib_f[] = {
	//{"getObject", luaGetInstance},
	//{"newInstance", luaAddNewInstance},
	{"CreateRenderBatch", LuaCreateRenderBatch},
	{"RenderBatch", LuaRenderBatch},
	{"UpdateSetting", LuaUpdateRenderSetting},
	{"UpdateBlendSettting", LuaUpdateBlendSetting},
	{NULL, NULL}
	};

	luaL_setfuncs(luaState, objectlib_m, 0);
	luaL_newlib(luaState, objectlib_f);

	return 1;
}
