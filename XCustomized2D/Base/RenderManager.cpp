#include "RenderManager.h"
#include "GameObject.h"
#include "Renderer.h"

#include "../Util/LogUtil.hpp"
#include "../Util/UuidUtill.hpp"
#include <GL3/gl3w.h>

RenderManager * RenderManager::pInstance = nullptr;

bool RenderManager::CheckUuidExisted(const std::string & uuid)
{
	if (renderHandleGroup.find(uuid) != renderHandleGroup.end())
	{

		return true;
	}

	return false;
}

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

std::string RenderManager::CreateBatch(BufferUsage bufferUsage, std::vector<int>& indices, std::vector<float>& vertices, std::vector<void*>& formats,
	std::vector<int>& elementLength, std::vector<int>& elementSize, bool needNormalize)
{
	Renderer* renderer = Renderer::getInstance();

	GLuint renderHandle = renderer->CreateRenderBatch(bufferUsage, sizeof(indices), &indices[0], sizeof(vertices), &vertices[0], formats.size(), &formats[0],
		&elementLength[0], &elementSize[0], FLOAT_DATA, needNormalize);

	std::string uuid = UuidUtil::GenerateUuid();
	while (CheckUuidExisted(uuid))	//get a empty uuid
	{
		uuid = UuidUtil::GenerateUuid();
	}

	renderHandleGroup[uuid] = renderHandle;

	return uuid;
}

void RenderManager::RenderBatch(const std::string & uuid, const std::string & shaderFolder, const std::string & shaderName, std::map<std::string, std::string>& textureGroup, std::map<std::string, std::any>& uniformInfoGroup, size_t indicesSize, size_t updateOffset, size_t updateSize, void * updateData)
{
	auto handleIter = renderHandleGroup.find(uuid);
	if (handleIter == renderHandleGroup.end())
	{
		LogUtil::printError("Unexisted render batch! uuid:"  + uuid);
		return;
	}

	Renderer* renderer = Renderer::getInstance();
	renderer->RenderBatch(handleIter->second, shaderFolder, shaderName, textureGroup, uniformInfoGroup, indicesSize, updateOffset, updateSize, updateData);
}

void RenderManager::StartRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void RenderManager::FinishRender()
{
}
