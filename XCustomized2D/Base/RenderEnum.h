#pragma once
#ifndef _RENDER_ENUM_H_
#define _RENDER_ENUM_H_
#include <GL/glcorearb.h>

enum BufferUsage {
	STATIC_DRAW = GL_STATIC_DRAW,
	DYNAMIC_DRAW = GL_DYNAMIC_DRAW

};

enum DataFormat {
	FLOAT_DATA = GL_FLOAT,
	INTEGER_DATA = GL_INT

};


#endif