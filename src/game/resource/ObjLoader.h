#ifndef OBJLOADER_H_
#define OBJLOADER_H_

#include <fstream>
#include <string>

#include "../OpenGL.h"
#include "Mesh.h"

namespace game {
namespace ObjLoader {

game::Mesh *load(std::string fname);

}
}

#endif
