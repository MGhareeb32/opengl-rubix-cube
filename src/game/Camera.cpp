#include "Camera.h"

namespace game {

Camera::Camera() : Entity() {
    ortho();
    lookAt(glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
}

Camera::~Camera() {
}

void Camera::lookAt(glm::vec3 eye, glm::vec3 coi, glm::vec3 upv) {
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

void Camera::ortho(GLfloat xleft, GLfloat xright,
                   GLfloat ybottom, GLfloat ytop,
                   GLfloat znear, GLfloat zfar) {
    glm::vec3 near_ = glm::vec3(xleft, ybottom, znear);
    glm::vec3 far_ = glm::vec3(xright, ytop, zfar);
    glm::vec3 add = far_ + near_;
    glm::vec3 sub = far_ - near_;
    proj_ = glm::mat4(1);
    proj_[0][0] = 2 / sub.x;
    proj_[1][1] = 2 / sub.y;
    proj_[2][2] = -2 / sub.z;
    proj_[3][0] = -add.x / sub.x;
    proj_[3][1] = -add.y / sub.y;
    proj_[3][2] = -add.z / sub.z;
}

void Camera::persp(GLfloat fov, GLfloat aspect, GLfloat n, GLfloat f) {
    proj_ = glm::mat4(0);
    GLfloat tanHalfFovy = glm::tan(fov * M_PI / 360);
    proj_[0][0] = 1 / (aspect * tanHalfFovy);
    proj_[1][1] = 1 / (tanHalfFovy);
    proj_[2][2] = - (f + n) / (f - n);
    proj_[2][3] = - 1;
    proj_[3][2] = - (2 * f * n) / (f - n);
}

glm::mat4 Camera::getViewMatrix() {
    return transform_i();
}

}
