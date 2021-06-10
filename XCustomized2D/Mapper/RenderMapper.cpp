#include "RenderMapper.h"
#include "../Util/LuaUtil.h"
#include "../Base/Renderer.h"
#include <string>

using namespace std;

int RenderMapper::LuaCreateRenderBatch(lua_State * luaState)
{
	int stackIndex = -1;

	luaL_checktype(luaState, stackIndex, LUA_TBOOLEAN);
	bool needNormalized = lua_tostring(luaState, stackIndex--);


	luaL_checktype(luaState, stackIndex, LUA_TSTRING);
	string dataFormat = lua_tostring(luaState, stackIndex--);

	std::vector<int> elementSize = LuaUtil::ParseLuaIntegerTable(luaState, stackIndex--);
	std::vector<int> elementLength = LuaUtil::ParseLuaIntegerTable(luaState, stackIndex--);
	std::vector<int> formats = LuaUtil::ParseLuaIntegerTable(luaState, stackIndex--);
	std::vector<float> vertices = LuaUtil::ParseLuaFloatTable(luaState, stackIndex--);
	std::vector<int> indices = LuaUtil::ParseLuaIntegerTable(luaState, stackIndex--);

	std::vector<GLshort> realIndices;
	for (int index : indices)
	{
		realIndices.push_back(index);
	}

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

	DataFormat realDataFormat;
	if (dataFormat == "FLOAT")
	{
		realDataFormat = FLOAT_DATA;
	}
	else {
		realDataFormat = INTEGER_DATA;

	}


	//luaL_checktype(luaState, -3, LUA_T);

	GLuint handle = Renderer::getInstance()->CreateRenderBatch(bufferUsage, realIndices.size(), &realIndices[0], vertices.size(), &vertices[0],
		formats.size(), &realFormat[0], &elementLength[0], &elementSize[0], realDataFormat, needNormalized);
	

	return 1;
}

int RenderMapper::InitRenderFuncLibs(lua_State * luaState)
{
	luaL_newmetatable(luaState, RENDER_HELPER_NAMESPACE);
	/* metatable.__index = metatable */
	lua_pushvalue(luaState, -1);  /* duplicates the metatable */
	lua_setfield(luaState, -2, "__index");


	static const struct luaL_Reg objectlib_m[] = {
	/*{"setPosition", GameObjectBinder::luaSetPosition},
	{"setScale", GameObjectBinder::luaSetScale},
	{"setRotation", GameObjectBinder::luaSetRotation},
	{"setDead", GameObjectBinder::luaSetDead},

	{"getPosition", GameObjectBinder::luaGetPosition},
	{"getScale", GameObjectBinder::luaGetScale},
	{"getRotation", GameObjectBinder::luaGetRotation},
	{"getDeltaTime", GameObjectBinder::luaGetDeltaTime},
	{"getAccmulateTime", GameObjectBinder::luaGetAccmulateTime},
	{"getTagName", GameObjectBinder::luaGetTagName},

	{"playAudio",GameObjectBinder::luaPlayAudio},
	{"stopAudio",GameObjectBinder::luaStopAudio},
	{"isPlaying", GameObjectBinder::luaIsPlaying},*/

	{NULL, NULL}
	};

	static const struct luaL_Reg objectlib_f[] = {
	//{"getObject", luaGetInstance},
	//{"newInstance", luaAddNewInstance},
	{NULL, NULL}
	};

	luaL_setfuncs(luaState, objectlib_m, 0);
	luaL_newlib(luaState, objectlib_f);

	return 0;
}
