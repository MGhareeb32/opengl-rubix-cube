#include "Camera.h"

namespace game {

Camera::Camera(GLfloat xleft, GLfloat xright, GLfloat ybottom, GLfloat ytop,
        GLfloat znear, GLfloat zfar) {
    near_ = glm::vec3(xleft, ybottom, znear);
    far_ = glm::vec3(xright, ytop, zfar);
    lookAt(glm::vec3(.1f, .1f, .1f), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
}

Camera::~Camera() {
}

void Camera::lookAt(glm::vec3 eye, glm::vec3 coi, glm::vec3 upv) {
    std::cout << "lookAt" << std::endl;
    resetTransform();

    glm::vec3 newN = glm::normalize(eye - coi);
    glm::vec3 newU = glm::normalize(glm::cross(upv, newN));
    glm::vec3 newV = glm::cross(newN, newU);

    GLfloat angU = acos(glm::dot(newU, u())) * 180 / M_PI;
    glm::vec3 axisU = glm::cross(newU, u());
    rotate(-angU, axisU);

    GLfloat angV = acos(glm::dot(newV, v())) * 180 / M_PI;
    glm::vec3 axisV = glm::cross(newV, v());
    rotate(-angV, axisV);

    translate(eye);
}

glm::mat4 Camera::getProjectionMatrix() {
    glm::vec3 add = far_ + near_;
    glm::vec3 sub = far_ - near_;
    return glm::mat4(2 / sub.x, 0, 0, -add.x / sub.x,
                     0, 2 / sub.y, 0, -add.y / sub.y,
                     0, 0, -2 / sub.z, -add.z / sub.z,
                     0, 0, 0, 1);
}

glm::mat4 Camera::getViewMatrix() {
    return transform_i();
}

}
