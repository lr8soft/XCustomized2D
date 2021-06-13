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
		int indicesSize, int* indices,
		int verticesSize, void* vertices,
		int formatLength, void** formats,
		int* elementLength, int* elementSize, DataFormat dataFormat, bool needNormalize );

	void RenderBatch(
		GLuint batchHandle, const std::string& shaderFolder, const std::string& shaderName, 
		std::map<std::string, std::string>& textureGroup, std::map<std::string, std::any>& uniformInfoGroup,
		size_t indicesSize, size_t updateOffset = 0, size_t updateSize = 0, void* updateData = nullptr);


	void ReleaseBatch(GLuint batchHandle);

	/*
	//demo

	//define

	GLfloat vertices[] = {
	 1.0f, 1.0f,
	 1.0f,-1.0f,
	-1.0f,-1.0f,
	-1.0f, 1.0f
	};

	GLshort indices[6] = { 0, 1, 2, 2, 3, 0 };

	void* vertexFormat[] = { (void*)0};

	size_t elementLength[] = { 2 };

	size_t elementSize[] = { 0 };


	Renderer* renderer = Renderer::getInstance();
	auto handle  = renderer->CreateRenderBatch(STATIC_DRAW, sizeof(indices), indices, sizeof(vertices), vertices, 1,
		vertexFormat, elementLength, elementSize, FLOAT_DATA, false);


	auto image = TextureManager::getInstance()->GetTexture("Assets/Texture/test.png");

	std::map<std::string, std::string> imageList;
	imageList["tex"] = "Assets/Texture/test.png";

	glm::mat4 mvp_mat;
	mvp_mat = glm::translate(mvp_mat, glm::vec3(0));
	//mvp_mat = glm::scale(mvp_mat, glm::vec3(1));

	std::map<std::string, std::any> uniformInfo;
	uniformInfo["mvp_mat"] = mvp_mat;


	//render work
	renderer->RenderBatch(handle, "Test", "default", imageList, uniformInfo, sizeof(indices) / sizeof(GLushort));
	
	*/


};

#endif