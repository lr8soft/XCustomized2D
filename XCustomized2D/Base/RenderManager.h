#pragma once
#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

class GameObject;
class RenderManager {
private:
	static RenderManager* pInstance;
	
public:
	static RenderManager* getInstance();


	void ApplyRenderSettings();
	
	void StartRender();
	void OnRender(GameObject*);
	void FinishRender();

};


#endif