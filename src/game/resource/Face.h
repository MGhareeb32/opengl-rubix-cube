#ifndef FACE_H_
#define FACE_H_

#include "../OpenGL.h"
#include "../internal.h"
#include "Material.h"

namespace game {

class Face {
private:
    int nVertex_;
    GLuint vao_, vbo_[3], drawMode_;
public:
    Face(int vertexCount, glm::vec3 *vertex, glm::vec2 *uvmap,
         glm::vec3 *normal, GLint mode);
    int getVertexCount();
    void render();
    virtual ~Face();
};

}

#endif
