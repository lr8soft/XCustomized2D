#pragma once
#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_
#include <string>
#include <map>

#include "Renderer.h"

class GameObject;
class RenderManager {
private:
	static RenderManager* pInstance;
	
	std::map<std::string, unsigned int> renderHandleGroup;

public:
	static RenderManager* getInstance();


	void ApplyRenderSettings();

	void StartRender();
	void OnRender(GameObject*);
	void FinishRender();

};


#endif