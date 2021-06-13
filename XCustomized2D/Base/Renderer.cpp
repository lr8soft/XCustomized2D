#include "Renderer.h"
#include <GL3/gl3w.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderManager.h"
#include "TextureManager.h"

using namespace std;

Renderer* Renderer::pInstance = nullptr;
Renderer * Renderer::getInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new Renderer;
	}
	return pInstance;
}

GLuint Renderer::CreateRenderBatch(BufferUsage bufferUsage, int indicesSize, int* indices, int verticesSize, void* vertices,
	int formatLength, void** formats, int* elementLength, int* elementSize, DataFormat dataFormat, bool needNormalize)
{

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, bufferUsage);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

	for (size_t i = 0; i < formatLength; i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, *(elementLength + i), dataFormat, needNormalize, *(elementSize + i), *(formats + i));
	}

	return VAO;
}

void Renderer::RenderBatch(GLuint batchHandle, const std::string& shaderFolder, const std::string & shaderName,
	std::map<std::string, std::string>& textureGroup, std::map<std::string, std::any>& uniformInfoGroup, 
	size_t indicesSize, size_t updateOffset, size_t updateSize, void * updateData)
{
	GLuint shaderHandle = ShaderManager::getInstance()->bindProgram(shaderFolder, shaderName);


	size_t index = 0;
	//bind all texture

	TextureManager* texManager = TextureManager::getInstance();
	for (auto texIter = textureGroup.begin(), texIterEnd = textureGroup.end(); texIter != texIterEnd; texIter++, index++)
	{
		auto loc = glGetUniformLocation(shaderHandle, texIter->first.c_str());	//find texture entrance
		GLuint texHandle = texManager->GetTexture(texIter->second)->tbo;	//find texture handle

		glActiveTexture(GL_TEXTURE0 + index);
		glUniform1i(loc, index);
		glBindTexture(GL_TEXTURE_2D, texHandle);
	}

	//send all uniform data to shader
	for (auto uniformIter = uniformInfoGroup.begin(), uniformIterEnd = uniformInfoGroup.end(); uniformIter != uniformIterEnd; uniformIter++)
	{
		string typeName = uniformIter->second.type().name();
		if (typeName == "struct glm::tmat4x4<float,0>")	//send matrix
		{
			glm::mat4 matrix = any_cast<glm::mat4>(uniformIter->second);

			auto matrixLocation = glGetUniformLocation(shaderHandle, uniformIter->first.c_str());
			glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
		}

		else if (typeName == "struct glm::tvec4<float,0>")	//send vec4
		{
			glm::vec4 vecData = any_cast<glm::vec4>(uniformIter->second);

			auto vecLocation = glGetUniformLocation(shaderHandle, uniformIter->first.c_str());
			glUniform4fv(vecLocation, 1, glm::value_ptr(vecData));

		}

		else if (typeName == "struct glm::tvec3<float,0>") //send vec3
		{
			glm::vec3 vecData = any_cast<glm::vec3>(uniformIter->second);

			auto vecLocation = glGetUniformLocation(shaderHandle, uniformIter->first.c_str());
			glUniform3fv(vecLocation, 1, glm::value_ptr(vecData));

		}

		else if (typeName == "float")	//send float
		{
			float value = any_cast<float>(uniformIter->second);
			glUniform1f(glGetUniformLocation(shaderHandle, uniformIter->first.c_str()), value);
		}

	}

	if (updateSize > 0)	//update array buffer data
	{
		glBufferSubData(GL_ARRAY_BUFFER, updateOffset, updateSize, updateData);
	}

	glBindVertexArray(batchHandle);

    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
	
}

void Renderer::ReleaseBatch(GLuint batchHandle)
{
	glDeleteVertexArrays(1, &batchHandle);
}

