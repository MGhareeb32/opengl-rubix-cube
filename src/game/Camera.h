#ifndef CAMERA_H_
#define CAMERA_H_

#include "OpenGL.h"
#include "Entity.h"
#include "Internal.h"

namespace game {

class Camera : public Entity {
    glm::vec3 near_, far_;
public:
    Camera(GLfloat xleft = -1, GLfloat xright = 1,
           GLfloat ybottom = -1, GLfloat ytop = 1,
           GLfloat znear = -1, GLfloat zfar = 1);
    virtual ~Camera();

    void lookAt(glm::vec3 eye, glm::vec3 coi, glm::vec3 upv);

    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();
};

}

#endif
