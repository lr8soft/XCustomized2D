#pragma once
#ifndef _ENGINE_FRAMEWORK_H_
#include <GLFW/glfw3.h>
#include "Util/Timer.h"
class EngineFramework {
private:
	/*STATIC AREA*/
	static EngineFramework *pInstance;
	static void FrameResize(GLFWwindow* screen, int w, int h);
	static void FramePos(GLFWwindow* screen, int x, int y);
	static void FrameCurseUpdate(GLFWwindow* screen, double x, double y);
	static void FrameScrollUpdate(GLFWwindow* screen, double x, double y);

	GLFWwindow *pScreen = nullptr, *tScreen = nullptr;
	bool isFrameTerminate = false;
	bool isFullScreen = false;

	EngineFramework();

public:
	static EngineFramework* getInstance();
	bool getFrameTerminate();
	GLFWwindow* getScreen();

	void FrameInit();
	void FrameLoop();
	void FrameFinalize();
};


#endif