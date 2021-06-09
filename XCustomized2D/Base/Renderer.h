#pragma once
#ifndef _OGL_RENDERER_H_
#define _OGL_RENDERER_H_
#include "RenderEnum.h"
#include "Image.h"

#include <any>
#include <string>
#include <map>

#include  <GL/glcorearb.h>
class Renderer {
private:
	static Renderer* pInstance;

public:
	static Renderer* getInstance();

	GLuint CreateRenderBatch(BufferUsage bufferUsage,
		size_t indicesSize, GLshort* indices,
		size_t verticesSize, void* vertices,
		size_t formatLength, void** formats, 
		size_t* elementLength, size_t* elementSize, DataFormat dataFormat, bool needNormalize );

	void RenderBatch(
		GLuint batchHandle, const std::string& shaderFolder, const std::string& shaderName, 
		std::map<std::string, std::shared_ptr<Image>>& textureGroup, std::map<std::string, std::any>& uniformInfoGroup,
		size_t indicesSize, size_t updateSize = 0, void* updateData = nullptr);


	void ReleaseBatch(GLuint batchHandle);



};

#endif