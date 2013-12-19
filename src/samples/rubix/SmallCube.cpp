#include "SmallCube.h"

// SMALL CUBE

SmallCube::SmallCube(glm::vec3 p, game::Mesh *flat, game::Mesh *rubix) {
    selected_ = false;
    spin_axis_ = glm::vec3(1, 0, 0);
    glm::vec3 c = p;
    int dir[6][3] = { { 1, 0, 0 }, { -1, 0, 0 },
                      { 0, 1, 0 }, { 0, -1, 0 },
                      { 0, 0, 1 }, { 0, 0, -1 } };
    for (GLint i = 0; i < 6; i++) {
        // create
        glm::vec3 v = glm::vec3(dir[i][0], dir[i][1], dir[i][2]);
        GLdouble diffAng = acos(glm::dot(glm::normalize(v), glm::normalize(c)))
                         * 180 / M_PI;
        std::string name = std::string("small") + char(i + '0');
        Entity* small = addChild
            (name, new CubeFace(diffAng > 60, flat, rubix, p + v));
        // position
        GLdouble rot = -acos(glm::dot(v, small->v())) * 180 / M_PI;
        glm::vec3 axis = glm::cross(v, small->v());
        small->scale(glm::vec3(v.x ? v.x : 1, v.y ? v.y : 1, v.z ? v.z : 1));
        if (glm::dot(axis, axis) > EPS)
            small->rotate(rot, axis);
        small->translate(v);
    }
    scale(glm::vec3(.5f, .5f, .5f));
    translate(p);
}

SmallCube::~SmallCube() {
}

void SmallCube::update() {
    if (abs(spin_ang_) >= 5) {
        GLfloat d = (spin_ang_ > 0 ? -1 : 1) * 10.f;
        spin_ang_ += d;
        rotate(d, spin_axis_, glm::vec3(0, 0, 0));
    } else {
        spin_ang_ = 0;
    }
    std::vector<std::string> ch = childrenNames();
    for (int i = 0; i < ch.size(); ++i)
        ((CubeFace*)getChild(ch[i]))->update();
}

void SmallCube::render() {
    std::vector<std::string> ch = childrenNames();
    for (int i = 0; i < ch.size(); ++i)
        ((CubeFace*)getChild(ch[i]))->render(selected_);
}

// CUBE FACE

CubeFace::CubeFace(bool f, game::Mesh *flat, game::Mesh *rubix, glm::vec3 p) {

    static game::Material* COLORS[7]
        = { (game::Material*)game::ResMgr::load("res/mesh/rubix/rubix-1.mtl"),
            (game::Material*)game::ResMgr::load("res/mesh/rubix/rubix-6.mtl"),
            (game::Material*)game::ResMgr::load("res/mesh/rubix/rubix-4.mtl"),
            (game::Material*)game::ResMgr::load("res/mesh/rubix/rubix-5.mtl"),
            (game::Material*)game::ResMgr::load("res/mesh/rubix/rubix-2.mtl"),
            (game::Material*)game::ResMgr::load("res/mesh/rubix/rubix-3.mtl"),
            (game::Material*)game::ResMgr::load("res/mesh/rubix/rubix-0.mtl") };

    set_mesh(f ? flat : rubix);
    int maxI = 0;
    for (int i = 1; i < 3; ++i)
        if (abs(p[maxI]) < abs(p[i]))
            maxI = i;
    set_mtl(f ? COLORS[6] : COLORS[(int) ((p[maxI] > 0 ? 0 : 1) + maxI * 2)]);
    if (!f) {
        game::MeshEntity *back = new game::MeshEntity(flat);
        back->set_mtl(COLORS[6]);
        addChild("back", back);
    }
}

CubeFace::~CubeFace() {
}

void CubeFace::render(bool selected) {
    float f = selected ? .8f + sin(game::global_time_ / 5.0) * .2f : 1.f;
    game::setUniformBlendColor(glm::vec4(0, 0, 0, f), glm::vec4(0, 0, 0, 1));
    game::MeshEntity::render();
}
