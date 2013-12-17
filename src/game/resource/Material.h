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
             glm::vec3 ks = glm::vec3(1.f, 1.f, 1.f), GLfloat ns = 0.f,
             GLfloat tr = 1.f);
    virtual ~Material();

    glm::vec3 ka() { return ka_; }
    glm::vec3 kd() { return kd_; }
    glm::vec3 ks() { return ks_; }
    GLfloat ns() { return ns_; }
    GLfloat tr() { return tr_; }

};

}

#endif
