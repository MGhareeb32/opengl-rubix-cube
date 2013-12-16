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
#include "ObjLoader.h"
#include "Camera.h"

std::ostream &operator<<(std::ostream &out, const glm::vec2 &vec);
std::ostream &operator<<(std::ostream &out, const glm::vec3 &vec);
std::ostream &operator<<(std::ostream &out, const glm::vec4 &vec);

namespace game {

void init(int argc, char **argv, GLint w, GLint h, std::string t);
void start(GLint f);

void setScene(Entity *scene, GLboolean destructOld = true);
Entity* getScene();
void setCamera(game::Camera* camera, GLboolean destructOld = true);
game::Camera* getCamera();
extern void setUniformFog(glm::vec4 color, GLfloat mag);

}

#endif
