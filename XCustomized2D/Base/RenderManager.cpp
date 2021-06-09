#include "RenderManager.h"
#include "GameObject.h"
#include <GL3/gl3w.h>
RenderManager * RenderManager::pInstance = nullptr;

RenderManager * RenderManager::getInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new RenderManager;
	}
	return pInstance;
}

void RenderManager::ApplyRenderSettings()
{
}

void RenderManager::StartRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderManager::OnRender(GameObject* pGameObject)
{

}

void RenderManager::FinishRender()
{
}
