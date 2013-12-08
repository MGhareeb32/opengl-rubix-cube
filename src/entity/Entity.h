#ifndef ENTITY_H_
#define ENTITY_H_

#include <map>
#include <vector>

#include "../OpenGL.h"
#include "../mesh/Mesh.h"

namespace entity {

class Entity {

    mesh::Mesh *mesh_;

    Entity* parent_;
    std::map<std::string, Entity*> children_;

    glm::mat4 transform_, transform_i_;
    glm::vec3 o_, n_, u_, v_;

public:

    Entity(mesh::Mesh *m = NULL);
    virtual ~Entity();

    mesh::Mesh* mesh() { return mesh_; }
    void set_mesh(mesh::Mesh *m) { mesh_ = m; }

    int childrenCount() { return children_.size(); }
    std::vector<std::string> childrenNames();
    Entity* getChild(std::string k) { return children_[k]; }
    bool hasChild(std::string k) { return children_[k]; }
    void addChild(std::string k, Entity *v);
    void removeChild(std::string k);

    glm::vec3 o() { return o_; }
    glm::vec3 n() { return n_; }
    glm::vec3 u() { return u_; }
    glm::vec3 v() { return v_; }

    void translate(glm::vec3 d);

    void scale(glm::vec3 s);

    void rotate(GLfloat angle, glm::vec3 axis, glm::vec3 offset);
    void rotate(GLfloat angle, glm::vec3 axis);

    void render(glm::mat4 t = glm::mat4(1));

};

}

#endif
