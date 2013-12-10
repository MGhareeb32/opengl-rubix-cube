#ifndef FACE_H_
#define FACE_H_

#include "OpenGL.h"

namespace game {

class Face {
private:
    int nVertex;
    GLuint vao, vbo[2], drawMode;
public:
    Face(int vertexCount, glm::vec3 *vertex, glm::vec4 *color, GLint mode);
    int getVertexCount();
    void render();
    virtual ~Face();
};

Face* new_square(glm::vec4 col);
Face* new_circle(glm::vec4 col, GLint nVertex);
Face* new_circle_gradient(glm::vec4 side, glm::vec4 col, GLint nVertex);
Face* new_arrow(glm::vec4 col);

}

#endif
