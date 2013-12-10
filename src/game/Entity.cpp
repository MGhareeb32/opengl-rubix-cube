#include "Entity.h"

namespace game {

Entity::Entity(game::Mesh *m) {
    mesh_ = m;

    parent_ = NULL;
    children_.clear();

    def_transform_ = glm::mat4(1);
    def_transform_i_ = glm::mat4(1);
    resetTransform();
}

Entity::~Entity() {
}

// CHILDREN

Entity* Entity::addChild(std::string k, Entity *v) {
    std::cout << "addChild " << k << std::endl;
    if (v->parent_)
        throw std::exception();
    children_[k] = v;
    v->parent_ = this;
    return v;
}

Entity* Entity::removeChild(std::string k) {
    std::cout << "removeChild " << k << std::endl;
    Entity *v = children_[k];
    children_[k]->parent_ = NULL;
    children_.erase(k);
    return v;
}

std::vector<std::string> Entity::childrenNames() {
    std::vector<std::string> out;
    std::map<std::string, Entity*>::iterator ch = children_.begin();
    while (ch != children_.end()) {
        out.push_back(ch->first);
        ch++;
    }
    return out;
}

// TRANSFORMATION

void Entity::resetTransform() {
    transform_ = def_transform_;
    transform_i_ = def_transform_i_;
    o_ = glm::vec3(0.f, 0.f, 0.f);
    u_ = glm::vec3(1.f, 0.f, 0.f);
    v_ = glm::vec3(0.f, 1.f, 0.f);
    n_ = glm::vec3(0.f, 0.f, 1.f);
    //
    std::map<std::string, Entity*>::iterator ch = children_.begin();
    while (ch != children_.end()) {
        ch->second->resetTransform();
        ch++;
    }
}

void Entity::fixTransform() {
    def_transform_ = transform_;
    def_transform_i_ = transform_i_;
    //
    std::map<std::string, Entity*>::iterator ch = children_.begin();
    while (ch != children_.end()) {
        ch->second->fixTransform();
        ch++;
    }
    //
    resetTransform();
}

void Entity::translate(glm::vec3 d) {
    glm::mat4 trans = glm::translate(d);
    glm::mat4 trans_i = glm::translate(-d);
    transform_ = trans * transform_;
    transform_i_ = transform_i_ * trans_i;
    o_ = glm::vec3(trans * glm::vec4(o_, 1.f));
    //
    std::map<std::string, Entity*>::iterator ch = children_.begin();
    while (ch != children_.end()) {
        ch->second->translate(d);
        ch++;
    }
}

void Entity::scale(glm::vec3 s, glm::vec3 offset) {
    glm::mat4 trans = glm::translate(-offset);
    glm::mat4 trans_i = glm::translate(offset);
    glm::mat4 scl = glm::scale(s);
    glm::mat4 scl_i = glm::scale(1.f / s);
    transform_ = trans * scl * trans_i * transform_;
    transform_i_ = transform_i_ * trans_i * scl_i * trans;
    u_ = glm::vec3(scl * glm::vec4(u_, 1.f));
    v_ = glm::vec3(scl * glm::vec4(v_, 1.f));
    n_ = glm::vec3(scl * glm::vec4(n_, 1.f));
    //
    std::map<std::string, Entity*>::iterator ch = children_.begin();
    while (ch != children_.end()) {
        ch->second->scale(s, glm::vec3(transform_ * glm::vec4(offset, 0)));
        ch++;
    }
}

void Entity::rotate(GLfloat angle, glm::vec3 axis, glm::vec3 offset) {
    glm::mat4 trans = glm::translate(offset);
    glm::mat4 trans_i = glm::translate(-offset);
    glm::mat4 rot = glm::rotate(angle, axis);
    glm::mat4 rot_i = glm::rotate(-angle, axis);
    transform_ = trans * rot * trans_i * transform_;
    transform_i_ = transform_i_ * trans_i * rot_i * trans;
    o_ = glm::vec3(trans * rot * trans_i * glm::vec4(o_, 1.f));
    u_ = glm::vec3(rot * glm::vec4(u_, 1.f));
    v_ = glm::vec3(rot * glm::vec4(v_, 1.f));
    n_ = glm::vec3(rot * glm::vec4(n_, 1.f));
    //
//    axis = glm::vec3(transform_i_ * glm::vec4(axis, 1.f));
    std::map<std::string, Entity*>::iterator ch = children_.begin();
//    offset = o_ - glm::vec3(transform_ * glm::vec4(offset, 1.f));
    while (ch != children_.end()) {
        ch->second->rotate(angle, axis, offset);
        ch++;
    }
}

// UPDATE

void Entity::update() {
    // render children
    std::map<std::string, Entity*>::iterator ch = children_.begin();
    while (ch != children_.end()) {
        ch->second->update();
        ch++;
    }
}

// RENDER

void Entity::render() {
    // render self
    if (mesh_)
        mesh_->render(transform_);
    // render children
    std::map<std::string, Entity*>::iterator ch = children_.begin();
    while (ch != children_.end()) {
        ch->second->render();
        ch++;
    }
}

}
