#include "Material.h"

namespace game {

Material::Material(std::string uid,
                   glm::vec3 ka,
                   glm::vec3 kd,
                   glm::vec3 ks, GLfloat ns,
                   GLfloat tr)
    : Resource(uid) {
    ka_ = ka;
    kd_ = kd;
    ks_ = ks;
    ns_ = ns;
    tr_ = tr;
}

Material::~Material() {
}

}
