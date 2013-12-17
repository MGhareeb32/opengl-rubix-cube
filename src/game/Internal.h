#ifndef INTERNAL_H_
#define INTERNAL_H_

#include <algorithm>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>

#include "../../include/Angel.h"

#include "../../include/glm/glm.hpp"
#include "../../include/glm/gtc/type_ptr.hpp"
#include "../../include/glm/gtx/transform.hpp"
#include "../../include/glm/gtx/transform2.hpp"
#include "../../include/glm/gtc/matrix_transform.hpp"
#include "../../include/glm/gtc/quaternion.hpp"

#include "OpenGL.h"

namespace game {

extern GLboolean mouse_down_[3], mouse_click_[3];
extern glm::vec2 mouse_pos_, mouse_pos_prev_;
extern GLboolean key_down_[256], key_click_[256];
extern GLint global_time_;

extern void setUniformModelMatrix(glm::mat4 f);
extern void setUniformViewMatrix(glm::mat4 f);

class Material;
extern void mtlSet(Material* mtl);

extern void fogSet(glm::vec4 color, GLfloat mag);

extern void setUniformBlendColor(glm::vec4 c, glm::vec4 b);

}
#endif
