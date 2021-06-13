#include <thread>
#include <GL3/gl3w.h>
#include <string>
#include "EngineFramework.h"
#include "FrameInfo.h"

#include "Util/LogUtil.hpp"
#include "EngineFramework.h"

#include "Util/LuaUtil.h"
#include "ThirdParty/lua/lua.h"

EngineFramework* EngineFramework::pInstance = nullptr;

EngineFramework::EngineFramework()
{
}
void EngineFramework::FrameInit()
{
	float smallSize = FrameInfo::ScreenWidth > FrameInfo::ScreenHeight ? FrameInfo::ScreenHeight : FrameInfo::ScreenWidth;
	float absWidth = smallSize / (float)FrameInfo::ScreenWidth;
	float absHeight = smallSize / (float)FrameInfo::ScreenHeight;

	FrameInfo::FrameRight = absWidth;
	FrameInfo::FrameLeft = -absWidth;
	FrameInfo::FrameTop = absHeight;
	FrameInfo::FrameBottom = -absHeight;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, false);//Auto change size

#ifndef _DEBUG
	glfwWindowHint(GLFW_SAMPLES, 4);//4x MSAA
	//glEnable(GL_MULTISAMPLE);
#endif

	GLFWmonitor* primaryMonitor = isFullScreen ? glfwGetPrimaryMonitor() : nullptr;
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	tScreen = glfwCreateWindow(1, 1, "ThreadInitHelper", nullptr, nullptr);
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
	pScreen = glfwCreateWindow(FrameInfo::ScreenWidth, FrameInfo::ScreenHeight, "NewHorizon", primaryMonitor, tScreen);
	glfwMakeContextCurrent(pScreen);

#ifndef _DEBUG
	//glfwSetInputMode(pScreen, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//capture cursor
#endif
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowPos(pScreen, (mode->width - FrameInfo::ScreenWidth) / 2, (mode->height - FrameInfo::ScreenHeight) / 2);
	if (pScreen == nullptr) {
		LogUtil::printError("Failed to create window!\n");
		exit(-1);
	}

	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(pScreen, FrameResize);
	glfwSetWindowPosCallback(pScreen, FramePos);

	glfwSetCursorPosCallback(pScreen, FrameCurseUpdate);
	glfwSetScrollCallback(pScreen, FrameScrollUpdate);

	gl3wInit();






	//lua_rawgeti(L, -1, 1);


	//lua_pushstring(L, "tex");
	//lua_gettable(L, -2);

	

	
	//std::string info = lua_tostring(L, -1);
	//lua_tostring(L, -2);

	//LogUtil::printError();
	//auto strList = LuaUtil::ParseLuaStringTable(L, -1);
	//LogUtil::printError(info);
	//LogUtil::printError(strList[1]);
}

void EngineFramework::FrameLoop()
{
	//EngineManager* instance = EngineManager::getInstance();

	///std::thread logicalThread(&EngineManager::onLogicalWork, instance);
	//logicalThread.detach();

	//instance->applyRenderSettings();

	lua_State* L = LuaUtil::CreateNewEvon();
	LuaUtil::LoadLuaFile(L, "test.lua");
	LuaUtil::InvokeLuaFunction(L, "TestFunc", 0, {}, false, "GameObject");

	while (!glfwWindowShouldClose(pScreen)) {
		glClear(GL_COLOR_BUFFER_BIT);

		LuaUtil::InvokeLuaFunction(L, "OnRender", 0, {}, false, "GameObject");

		glfwSwapBuffers(pScreen);
		glfwPollEvents();
	}
	isFrameTerminate = true;

	glfwDestroyWindow(pScreen);
	glfwDestroyWindow(tScreen);
	glfwTerminate();
}

void EngineFramework::FrameFinalize()
{ 
	delete pInstance;
	pInstance = nullptr;
}


void EngineFramework::FrameResize(GLFWwindow * screen, int w, int h)
{
	if (w > 0 && h > 0) {
		glViewport(0, 0, w, h);

		float smallSize = w > h ? h : w;
		float absWidth = smallSize / (float)w;
		float absHeight = smallSize / (float)h;

		FrameInfo::FrameRight = absWidth;
		FrameInfo::FrameLeft = -absWidth;
		FrameInfo::FrameTop = absHeight;
		FrameInfo::FrameBottom = -absHeight;

		FrameInfo::ScreenHeight = h;
		FrameInfo::ScreenWidth = w;
	}
}

void EngineFramework::FramePos(GLFWwindow * screen, int x, int y)
{
}

void EngineFramework::FrameCurseUpdate(GLFWwindow * screen, double x, double y)
{
	//EngineManager* instance = EngineManager::getInstance();
	//instance->onMouseUpdate(x, y);
}


void EngineFramework::FrameScrollUpdate(GLFWwindow * screen, double x, double y)
{
	//EngineManager* instance = EngineManager::getInstance();
	//instance->onScrollUpdate(x, y);
}

bool EngineFramework::getFrameTerminate()
{
	return isFrameTerminate;
}

EngineFramework * EngineFramework::getInstance()
{
	if (pInstance == nullptr) {
		pInstance = new EngineFramework;
	}
	return pInstance;

}

GLFWwindow * EngineFramework::getScreen()
{
	return pScreen;
}