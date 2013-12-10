#include "Face.h"

namespace game {

Face::Face(int vertexCount, glm::vec3 *vertex, glm::vec4 *color, GLint mode) {
//	cout << "V|";
//	for (int i = 0; i < vertexCount; ++i)
//		cout << vertex[i].x << "," << vertex[i].y << "," << vertex[i].z << "|";
//	cout << " C|";
//	for (int i = 0; i < vertexCount; ++i)
//		cout << color[i].x << "," << color[i].y << "," << color[i].z << ","
//		     << color[i].w << "|";
//	cout << endl;
    nVertex = vertexCount;
	drawMode = mode;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(2, &vbo[0]);

    // position
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 nVertex * sizeof(glm::vec3), vertex, GL_STATIC_DRAW);
    // set as attr 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // rgba
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 nVertex * sizeof(glm::vec4), color, GL_STATIC_DRAW);
    // set as attr 1
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

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
    glDeleteBuffers(2, &vbo[0]);
    // disable attrs
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

}
