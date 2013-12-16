#ifndef SMALLCUBE_H_
#define SMALLCUBE_H_

#include "../../game/Game.h"

const GLfloat EPS = 0.0001f;

static glm::vec4 COLORS[7]
    = { glm::vec4(1, 0, 0, 1),
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 0, 1, 1),
        glm::vec4(1, 0, 1, 1),
        glm::vec4(1, 1, 0, 1),
        glm::vec4(1, 0, .2, 1) };

class SmallCube : public game::MeshEntity {
    bool selected_;
    GLfloat spin_ang_;
    glm::vec3 spin_axis_;
public:
    SmallCube(glm::vec3 pos, game::Mesh *flat, game::Mesh *rubix);
    virtual ~SmallCube();
    void update();
    void render();
    GLfloat spin_ang() { return spin_ang_; }
    void set_spin_ang(GLfloat ang) { spin_ang_ = ang; }
    void set_spin_axis(glm::vec3 axis) { spin_axis_ = axis; }
    bool* selected() { return &selected_; }
};

class CubeFace : public game::MeshEntity {
    glm::vec4 color_;
public:
    CubeFace(game::Mesh *m, glm::vec3 p);
    virtual ~CubeFace();
    void render(bool selected);
};


#endif
