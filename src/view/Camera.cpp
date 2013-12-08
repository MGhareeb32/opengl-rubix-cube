#include "Camera.h"

namespace camera {

Camera::Camera(GLfloat xleft, GLfloat xright, GLfloat ybottom, GLfloat ytop,
               GLfloat znear, GLfloat zfar) {
    near_ = glm::vec3(xleft, ybottom, znear);
    far_ = glm::vec3(xright, ytop, zfar);
    lookAt(glm::vec3(.1, .1, .1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
}

Camera::~Camera() {
}

void Camera::getBases(glm::vec3 *v) {
}

void Camera::lookAt(glm::vec3 eye, glm::vec3 coi, glm::vec3 upv) {
    glm::vec3 n = glm::normalize(coi - eye);
    glm::vec3 u = glm::normalize(glm::cross(upv, n));
    glm::vec3 v = glm::cross(n, u);

    matrix = glm::transpose(glm::mat4(glm::vec4(u, 0),
                                      glm::vec4(v, 0),
                                      glm::vec4(n, 0),
                                      glm::vec4(0, 0, 0, 1)))
           * glm::translate(matrix, -eye);
}

void Camera::move(const glm::vec3 p) {
    matrix = glm::translate(-p) * matrix;
}

void Camera::rotate(GLfloat ang, int axis) {
    matrix = glm::rotate(ang, glm::vec3(0, 0, 1)) * matrix;
}

glm::mat4 Camera::getProjectionMatrix() {
    glm::vec3 add = far_ + near_;
    glm::vec3 sub = far_ - near_;
    return glm::mat4
        (2 / sub.x, 0       , 0         , -add.x / sub.x,
         0       , 2 / sub.y, 0         , -add.y / sub.y,
         0       , 0        , -2 / sub.z, -add.z / sub.z,
         0       , 0        , 0         , 1             );
}

glm::mat4 Camera::getViewMatrix() {
    return matrix;
}

}
