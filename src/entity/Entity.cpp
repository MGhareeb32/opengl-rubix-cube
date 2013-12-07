#include "Entity.h"

namespace entity {

Entity::Entity(mesh::Mesh *m) {
    transform_ = glm::mat4(1);
    mesh_ = m;
}

Entity::~Entity() {
}

// CHILDREN

std::vector<std::string> Entity::childrenNames() {
    std::vector<std::string> out;
    std::map<std::string, Entity*>::iterator ch = children_.begin();
    while (ch != children_.end()) {
        out.push_back(ch->first);
        ch++;
    }
    return out;
}

// RENDER

void Entity::render(glm::mat4 t) {
    // update transformation
    glm::mat4 transform = transform_ * t;
    // render self
    if (mesh_)
        mesh_->render(transform);
    // render children
    std::map<std::string, Entity*>::iterator ch = children_.begin();
    while (ch != children_.end()) {
        ch->second->render(transform);
        ch++;
    }
}

}
