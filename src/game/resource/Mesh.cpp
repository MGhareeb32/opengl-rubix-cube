#include "Mesh.h"

namespace game {

Mesh::Mesh(std::string uid) : Resource(uid) {
}

Mesh::~Mesh() {
    for (int i = 0; i < faces.size(); ++i)
        faces[i]->~Face();
}

void Mesh::render(glm::mat4 transformation) {
    game::setUniformModelMatrix(transformation);
//    glUniformMatrix4fv(unifromModelMatrix, 1, GL_FALSE, &transformation[0][0]);
    for (int i = 0; i < faces.size(); ++i)
        faces[i]->render();
}

//Mesh *new_pyramid() {
//    glm::vec4 col[3][3];
//    for (int i = 0; i < 3; ++i)
//        col[0][i] = glm::vec4(1.f, 0.f, 0.f, .4f);
//    for (int i = 0; i < 3; ++i)
//        col[1][i] = glm::vec4(0.f, 1.f, 0.f, .4f);
//    for (int i = 0; i < 3; ++i)
//        col[2][i] = glm::vec4(0.f, 0.f, 1.f, .4f);
//    glm::vec3 triangle[6][3] = {
//    // back
//        { glm::vec3(+.0f, +.0f, 1.f),
//          glm::vec3(-.5f, -.5f, 0.f),
//          glm::vec3(+.5f, -.5f, 0.f) },
//    // left
//        { glm::vec3(+.0f, +.0f, 1.f),
//          glm::vec3(-.5f, -.5f, 0.f),
//          glm::vec3(-.5f, +.5f, 0.f) },
//    // bottom
//        { glm::vec3(-.5f, -.5f, 0.f),
//          glm::vec3(-.5f, +.5f, 0.f),
//          glm::vec3(+.5f, -.5f, 0.f) },
//    // front
//        { glm::vec3(+.0f, +.0f, 1.f),
//          glm::vec3(-.5f, +.5f, 0.f),
//          glm::vec3(+.5f, +.5f, 0.f) },
//    // right
//        { glm::vec3(+.0f, +.0f, 1.f),
//          glm::vec3(+.5f, -.5f, 0.f),
//          glm::vec3(+.5f, +.5f, 0.f) },
//    // bottom
//        { glm::vec3(-.5f, +.5f, 0.f),
//          glm::vec3(+.5f, -.5f, 0.f),
//          glm::vec3(+.5f, +.5f, 0.f) },
//    };
//    // build
//    Mesh *out = new Mesh();
//    for (int i = 0; i < 6; ++i)
//        out->addFace(new Face(3, triangle[i], col[i % 3], GL_TRIANGLE_STRIP));
//    return out;
//}

}
