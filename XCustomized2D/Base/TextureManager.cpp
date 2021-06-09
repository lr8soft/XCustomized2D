#include "TextureManager.h"
#include "../Util/ImageLoader.h"

using namespace std;
TextureManager * TextureManager::pInstance = nullptr;
TextureManager * TextureManager::getInstance()
{
	if (pInstance == nullptr)
		pInstance = new TextureManager;
	return pInstance;
}

std::shared_ptr<Image> TextureManager::GetTexture(const std::string & path)
{
	auto targetIter = textureGroup.find(path);
	if (targetIter != textureGroup.end())	//existed
	{
		return targetIter->second;
	}
	else {	//new texture
		shared_ptr<Image> newImage = make_shared<Image>();

		//load texture successfully
		if (ImageLoader::loadTextureFromFile(newImage->tbo, path.c_str(), newImage->width, newImage->height, newImage->channel))
		{
			textureGroup[path] = newImage;
			return newImage;
		}
		
	}
	return nullptr;
}

bool TextureManager::ReleaseTexture(const std::string & path)
{
	auto targetIter = textureGroup.find(path);
	if (targetIter != textureGroup.end())	//existed
	{
		return false;
	}

	ImageLoader::releaseTextureByHandle(targetIter->second->tbo);
	return textureGroup.erase(path);
}
