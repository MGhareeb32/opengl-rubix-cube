#ifndef ENTITY_H_
#define ENTITY_H_

#include <map>
#include <vector>

#include "../OpenGL.h"
#include "../mesh/Mesh.h"

namespace entity {

class Entity {
    glm::mat4 transform_;
    mesh::Mesh *mesh_;
    std::map<std::string, Entity*> children_;
public:
    Entity(mesh::Mesh *m = NULL);
    virtual ~Entity();

    void set_mesh(mesh::Mesh *m) { mesh_ = m; }

    glm::mat4& transform() { return transform_; }

    int childrenCount() { return children_.size(); }
    std::vector<std::string> childrenNames();
    Entity* getChild(std::string k) { return children_[k]; }
    void addChild(std::string k, Entity *v) { children_[k] = v; }
    void removeChild(std::string k) { children_.erase(k); }
    bool hasChild(std::string k) { return children_[k]; }

    void render(glm::mat4 t = glm::mat4(1));
};

}

#endif
