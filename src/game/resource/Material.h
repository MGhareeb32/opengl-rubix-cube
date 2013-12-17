#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "../Internal.h"
#include "Resource.h"

namespace game {

class Material : public Resource {
    glm::vec3 ka_, kd_, ks_;
    GLfloat ns_, tr_;
public:
    Material(std::string uid,
             glm::vec3 ka = glm::vec3(.2f, .2f, .2f),
             glm::vec3 kd = glm::vec3(.8f, .8f, .8f),
             glm::vec3 ks = glm::vec3(1.f, 1.f, 1.f), GLfloat ns_ = 0.f,
             GLfloat tr = 1.f);
    virtual ~Material();
};

}

#endif
