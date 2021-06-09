#define STB_IMAGE_IMPLEMENTATION
#include "ImageLoader.h"
#include <GL3/gl3w.h>
#include "LogUtil.hpp"
#include <string>

void * ImageLoader::getTexturePointer(const char* tex, int &width, int &height, int &channels)
{
	stbi_set_flip_vertically_on_load(false);
	void* texture_ptr = stbi_load(tex, &width, &height, &channels, STBI_rgb_alpha);
	if (texture_ptr) {
		return texture_ptr;
	}
	else {
		return nullptr;
	}
}

bool ImageLoader::loadTextureFromFile(unsigned int &tbo, const char * imagePath, int & width, int & height, int & channels, bool filpUpsideDown)
{
	stbi_set_flip_vertically_on_load(filpUpsideDown);
	void* texture_ptr = stbi_load(imagePath, &width, &height, &channels, STBI_rgb_alpha);

	glGenTextures(1, &tbo);
	glBindTexture(GL_TEXTURE_2D, tbo);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (texture_ptr) {
		char infoFormat[256];
		if (channels == 1) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_ptr);//latter parameter is RGBA
			sprintf_s(infoFormat, sizeof(infoFormat), "Load image from %s format:%s", imagePath, "GREY");
			//LogUtil::printInfo( ("Load image from" + path + "format:GREY") );
			//std::cout << "[INFO] Load image from " << path << " format:GREY" << std::endl;
		}
		else if (channels == 2) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_ptr);//latter parameter is RGBA
			sprintf_s(infoFormat, sizeof(infoFormat), "Load image from %s format:%s", imagePath, "GREY ALPHA");
			//std::cout << "[INFO] Load image from " << path << " format:GREY ALPHA" << std::endl;
		}
		else if (channels == 3) {//RGB -> jpeg
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_ptr);//latter parameter is RGBA
			sprintf_s(infoFormat, sizeof(infoFormat), "Load image from %s format:%s", imagePath, "RGB");
			//std::cout << "[INFO] Load image from " << path << " format:RGB" << std::endl;
		}
		else if (channels == 4) {//rgba -> png
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_ptr);//both parameter are RGBA
			sprintf_s(infoFormat, sizeof(infoFormat), "Load image from %s format:%s", imagePath, "RGBA");
			//std::cout << "[INFO] Load image from " << path << " format:RGBA" << std::endl;
		}
		LogUtil::printInfo(infoFormat);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::string path = imagePath;
		LogUtil::printError("Can\'t load image " + path + " !" );

		return false;
	}
	glBindTexture(GL_TEXTURE_2D, 0);//Bind nothing.
	stbi_image_free(texture_ptr);

	return true;
}

void ImageLoader::releaseTextureByHandle(unsigned int tbo)
{
	glDeleteTextures(1, &tbo);
}



