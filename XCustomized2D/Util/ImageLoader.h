#pragma once
#ifndef _image_loader_
#define _image_loader_
#include "stb_image.h"
#include <gl/glcorearb.h>
#include <map>
#include <vector>
struct ImageStruct {
	GLuint tbo;
	int width;
	int height;
	int channel;
};
class ImageLoader
{
public:
	static void* getTexturePointer(const char* imagePath, int &width, int &height, int &channels);

	static bool loadTextureFromFile(unsigned int &tbo, const char* imagePath, int &width, int &height, int &channels, bool filpUpsideDown = false);

	static void releaseTextureByHandle(unsigned int tbo);
};

#endif 
