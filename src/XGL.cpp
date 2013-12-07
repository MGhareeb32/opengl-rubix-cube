#include "XGL.h"

void xglSetModelMatrix(glm::mat4 model) {
    glUniformMatrix4fv(unifromModelMatrix, 1, GL_FALSE, &model[0][0]);
}

void xglSetViewMatrix(glm::mat4 view) {
    glUniformMatrix4fv(unifromViewMatrix, 1, GL_FALSE, &view[0][0]);
}
