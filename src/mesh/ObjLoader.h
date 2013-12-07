#ifndef OBJLOADER_H_
#define OBJLOADER_H_

#include <fstream>
#include <string>

#include "../OpenGL.h"

#include "Face.h"
#include "Mesh.h"

using namespace mesh;

namespace objLoader {

Mesh *load(std::string fname);

}

#endif
