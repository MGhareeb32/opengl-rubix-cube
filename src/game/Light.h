#ifndef LIGHT_H_
#define LIGHT_H_

#include "Entity.h"

namespace game {

class Light : public Entity {
    glm::vec3 ambient_, diffuse_, specular_;
public:
    Light(glm::vec3 ambient = glm::vec3(1.f, 1.f, 1.f),
          glm::vec3 diffuse = glm::vec3(1.f, 1.f, 1.f),
          glm::vec3 specular = glm::vec3(1.f, 1.f, 1.f)) : Entity(),
        ambient_(ambient), diffuse_(diffuse), specular_(specular) {};
    ~Light() {};

    glm::vec3 ambient() { return ambient_; };
    void set_ambient(glm::vec3 ambient) { ambient_ = ambient; };
    glm::vec3 diffuse() { return diffuse_; };
    void set_diffuse(glm::vec3 diffuse) { diffuse_ = diffuse; };
    glm::vec3 specular() { return specular_; };
    void set_specular(glm::vec3 specular) { specular_ = specular; };
};

}

#endif
