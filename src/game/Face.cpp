#include "Face.h"

namespace game {

Face::Face(int vertexCount, glm::vec3 *vertex, glm::vec3 *normal,
        glm::vec4 *color, GLint mode) {

    nVertex = vertexCount;
	drawMode = mode;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(3, &vbo[0]);

    // position
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 nVertex * sizeof(glm::vec3), vertex, GL_STATIC_DRAW);
    // set as attr 0
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // normal
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 nVertex * sizeof(glm::vec3), normal, GL_STATIC_DRAW);
    // set as attr 1
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // rgba
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER,
                 nVertex * sizeof(glm::vec4), color, GL_STATIC_DRAW);
    // set as attr 2
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

int Face::getVertexCount() {
    return nVertex;
}

void Face::render() {
    glBindVertexArray(vao);
    glDrawArrays(drawMode, 0, nVertex);
}

Face::~Face() {
    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // delete buffers
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(3, &vbo[0]);
    // disable attrs
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

}
