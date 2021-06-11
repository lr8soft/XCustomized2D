#pragma once
#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_
#include <string>
#include <map>
#include <vector>
#include <any>

#include "Renderer.h"

class GameObject;
class RenderManager {
private:
	static RenderManager* pInstance;
	
	std::map<std::string, unsigned int> renderHandleGroup;

	bool CheckUuidExisted(const std::string& uuid);

public:
	static RenderManager* getInstance();


	void ApplyRenderSettings();

	std::string CreateBatch(BufferUsage bufferUsage,
		std::vector<GLshort>& indices,
		std::vector<float>& vertices,
		std::vector<void*>& formats,
		std::vector<int>& elementLength, std::vector<int>& elementSize, bool needNormalize);

	void RenderBatch(const std::string& uuid, const std::string& shaderFolder, const std::string& shaderName,
		std::map<std::string, std::string>& textureGroup, std::map<std::string, std::any>& uniformInfoGroup,
		size_t indicesSize, size_t updateOffset = 0, size_t updateSize = 0, void* updateData = nullptr);

	void StartRender();
	void FinishRender();

};


#endif