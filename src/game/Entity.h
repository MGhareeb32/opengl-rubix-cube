#ifndef ENTITY_H_
#define ENTITY_H_

#include <map>
#include <vector>

#include "Mesh.h"
#include "OpenGL.h"
#include "Internal.h"

namespace game {

class Entity {
    Entity* parent_;
    std::map<std::string, Entity*> children_;

    glm::mat4 def_transform_, def_transform_i_;
    glm::mat4 transform_, transform_i_;
    glm::vec3 o_, n_, u_, v_;

public:

    Entity();
    virtual ~Entity();

    int childrenCount() { return children_.size(); }
    std::vector<std::string> childrenNames();
    Entity* getChild(std::string k) { return children_[k]; }
    bool hasChild(std::string k) { return children_[k]; }
    Entity* addChild(std::string k, Entity *v);
    Entity* removeChild(std::string k);

    glm::mat4 transform() { return transform_; }
    glm::mat4 transform_i() { return transform_i_; }
    void resetTransform();
    void fixTransform();
    glm::vec3 o() { return o_; }
    glm::vec3 n() { return n_; }
    glm::vec3 u() { return u_; }
    glm::vec3 v() { return v_; }

    void translate(glm::vec3 d);

    void scale(glm::vec3 s, glm::vec3 offset);
    void scale(glm::vec3 s) { scale(s, o_); }

    void rotate(GLfloat angle, glm::vec3 axis,
                glm::vec3 offset = glm::vec3(0, 0, 0));
//    void rotate(GLfloat angle, glm::vec3 axis);

    virtual void update();
    virtual void render();
//    virtual bool preRender();
//    virtual bool postRender();

};

}

#endif
