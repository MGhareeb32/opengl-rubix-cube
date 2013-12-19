#include "Face.h"

namespace game {

Face::Face(int vertexCount, glm::vec3 *vertex, glm::vec2 *uvmap,
           glm::vec3 *normal, GLint mode) {

    nVertex_ = vertexCount;
	drawMode_ = mode;

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(3, &vbo_[0]);

    int attr_idx = 0;

    // position
    glBindBuffer(GL_ARRAY_BUFFER, vbo_[attr_idx]);
    glBufferData(GL_ARRAY_BUFFER,
                 nVertex_ * sizeof(glm::vec3), vertex, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attr_idx);
    glVertexAttribPointer(attr_idx, 3, GL_FLOAT, GL_FALSE, 0, 0);
    attr_idx++;

    // normal
    glBindBuffer(GL_ARRAY_BUFFER, vbo_[attr_idx]);
    glBufferData(GL_ARRAY_BUFFER,
                 nVertex_ * sizeof(glm::vec3), normal, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attr_idx);
    glVertexAttribPointer(attr_idx, 3, GL_FLOAT, GL_FALSE, 0, 0);
    attr_idx++;
}

int Face::getVertexCount() {
    return nVertex_;
}

void Face::render() {
    glBindVertexArray(vao_);
    glDrawArrays(drawMode_, 0, nVertex_);
}

Face::~Face() {
    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // delete buffers
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(3, &vbo_[0]);
    // disable attrs
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

}
