#ifndef GAME_H_
#define GAME_H_

#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "../../include/Angel.h"

#include "../../include/glm/glm.hpp"
#include "../../include/glm/gtc/type_ptr.hpp"
#include "../../include/glm/gtx/transform.hpp"
#include "../../include/glm/gtx/transform2.hpp"
#include "../../include/glm/gtc/matrix_transform.hpp"
#include "../../include/glm/gtc/quaternion.hpp"

#include "OpenGL.h"
#include "Entity.h"
#include "Camera.h"
#include "Light.h"
#include "resource/Mesh.h"
#include "MeshEntity.h"
#include "resource/ResMgr.h"

std::ostream &operator<<(std::ostream &out, const glm::vec2 &vec);
std::ostream &operator<<(std::ostream &out, const glm::vec3 &vec);
std::ostream &operator<<(std::ostream &out, const glm::vec4 &vec);

namespace game {

void init(int argc, char **argv, GLint w, GLint h, std::string t);
void start(GLint f);

void sceneSet(Entity *scene, GLboolean destructOld = true);
Entity* sceneGet();

void cameraSet(game::Camera* camera, GLboolean destructOld = true);
game::Camera* cameraGet();

game::Light* lightGet();

extern void fogSet(glm::vec4 color, GLfloat mag);

}

#endif
