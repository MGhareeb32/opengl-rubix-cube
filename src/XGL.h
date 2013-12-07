#ifndef XGL_H_
#define XGL_H_

#include "OpenGL.h"

extern GLint unifromModelMatrix, unifromViewMatrix;

void xglSetModelMatrix(glm::mat4 transformation);
void xglSetViewMatrix(glm::mat4 transformation);

#endif
