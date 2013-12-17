#ifndef LIGHT_H_
#define LIGHT_H_

#include "Entity.h"

namespace game {

class Light : public Entity {
    GLfloat ambient_;
public:
    Light(GLfloat a = .1f) : ambient_(a) {}
    virtual ~Light();
    float ambient() { return ambient_; };
};

}

#endif
