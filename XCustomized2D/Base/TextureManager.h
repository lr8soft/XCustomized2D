#pragma once
#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_
#include <string>
#include <map>
#include <memory>
#include "Image.h"
class TextureManager {
private:
	static TextureManager* pInstance;

	std::map<std::string, std::shared_ptr<Image>> textureGroup;

public:
	static TextureManager* getInstance();

	std::shared_ptr <Image> GetTexture(const std::string& path);

	bool ReleaseTexture(const std::string& path);

};


#endif