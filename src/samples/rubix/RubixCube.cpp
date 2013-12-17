#include "RubixCube.h"

RubixCube::RubixCube() {
    axes = game::ObjLoader::load("res/mesh/axes.obj");
    monkey = game::ObjLoader::load("res/mesh/monkey.obj");
    pyramid = game::ObjLoader::load("res/mesh/pyramid.obj");
    rubix = game::ObjLoader::load("res/mesh/rubix-face.obj");
    flat = game::ObjLoader::load("res/mesh/flat-face.obj");
    // initialize faces
//    set_mesh(axes);
    game::cameraSet(new game::Camera());
    // faces
    for (GLfloat x = -1.f; x <= +1.f; x += 1.f)
        for (GLfloat y = -1.f; y <= +1.f; y += 1.f)
            for (GLfloat z = -1.f; z <= +1.f; z += 1.f)
                if (x != y || y != z || z != 0.f)
                    addChild(std::string("cube") + char(childrenCount() + '0'),
                             new SmallCube(glm::vec3(x, y, z), flat, rubix));
    // 1
//    addChild("pyramid1", new game::Entity(pyramid));
//    getChild("pyramid1")->rotate(90.f, glm::vec3(0, 1, 0));
//    getChild("pyramid1")->translate(glm::vec3(1.f, 0.f, 0.f));
//    // 2
//    addChild("pyramid2", new game::Entity(pyramid));
//    getChild("pyramid2")->rotate (-90.f, glm::vec3(1, 0, 0));
//    getChild("pyramid2")->translate(glm::vec3(0.f, 1.f, 0.f));
//    // 3
//    addChild("pyramid3", new game::Entity(pyramid));
//    getChild("pyramid3")->translate(glm::vec3(0.f, 0.f, 1.f));
//     monkey
    scale(glm::vec3(.4f, .4f, .4f));
    game::lightGet()->translate(glm::vec3(0, 0, 100));
}

RubixCube::~RubixCube() {
    std::vector<std::string> ch = childrenNames();
    for (int i = 0; i < ch.size(); ++i) {
        game::Entity* c = getChild(ch[i]);
        removeChild(ch[i]);
        c->~Entity();
    }
    axes->~Mesh();
    monkey->~Mesh();
    pyramid->~Mesh();
    rubix->~Mesh();
    flat->~Mesh();
}

void RubixCube::update() {
    game::lightGet()->rotate(2.f, glm::vec3(0, 0, 1), glm::vec3(0, 0, 0));
    // camera
    game::Camera* myCamera = game::cameraGet();
    bool speed = game::key_down_[' '];
    if (game::key_down_['w'])
        myCamera->rotate(+(speed * 4 + 1), myCamera->u());
    if (game::key_down_['s'])
        myCamera->rotate(-(speed * 4 + 1), myCamera->u());

    if (game::key_down_['q'])
        myCamera->rotate(+(speed * 4 + 1), myCamera->n());
    if (game::key_down_['e'])
        myCamera->rotate(-(speed * 4 + 1), myCamera->n());

    if (game::key_down_['d'])
        myCamera->rotate(+(speed * 4 + 1), glm::vec3(0, 0, 1));
    if (game::key_down_['a'])
        myCamera->rotate(-(speed * 4 + 1), glm::vec3(0, 0, 1));

    if (game::key_down_['A'])
        myCamera->translate(-myCamera->u() * .1f);
    if (game::key_down_['D'])
        myCamera->translate(myCamera->u() * .1f);
    // select
    if (game::key_down_['1'])
        select(0, -1);
    if (game::key_down_['2'])
        select(0, 0);
    if (game::key_down_['3'])
        select(0, 1);
    if (game::key_down_['4'])
        select(1, -1);
    if (game::key_down_['5'])
        select(1, 0);
    if (game::key_down_['6'])
        select(1, 1);
    if (game::key_down_['7'])
        select(2, -1);
    if (game::key_down_['8'])
        select(2, 0);
    if (game::key_down_['9'])
        select(2, 1);
    // move
    if (game::key_down_['z'])
        spin(90);
    if (game::key_down_['x'])
        spin(-90);
    game::MeshEntity::update();
}

void RubixCube::select(int axis, GLfloat n) {
    glm::vec3 axes[3] = { glm::vec3(1, 0, 0),
                          glm::vec3(0, 1, 0),
                          glm::vec3(0, 0, 1) };
    // check
    std::vector<std::string> v = childrenNames();
    std::set<SmallCube*> good;
    bool can = true;
    for (int i = 0; i < v.size() && can; ++i) {
        SmallCube* ch = (SmallCube*)getChild(v[i]);
        glm::vec3 org = ch->o();
        can = abs(ch->spin_ang()) < EPS;
        if (n <= org[axis] + EPS && n >= org[axis] -EPS)
            good.insert(ch);
    }
    // select
    if (can)
        for (int i = 0; i < v.size(); ++i)
            if (good.find((SmallCube*)getChild(v[i])) != good.end())
                *((SmallCube*)getChild(v[i]))->selected() = true,
                ((SmallCube*)getChild(v[i]))->set_spin_axis(axes[axis]);
            else
                *((SmallCube*)getChild(v[i]))->selected() = false;
}

void RubixCube::spin(GLfloat ang) {
    // check
    std::vector<std::string> v = childrenNames();
    std::set<SmallCube*> good;
    bool can = true;
    for (int i = 0; i < v.size() && can; ++i) {
        SmallCube* ch = (SmallCube*)getChild(v[i]);
        glm::vec3 org = ch->o();
        can = abs(ch->spin_ang()) < EPS;
    }
    if (can)
        for (int i = 0; i < v.size(); ++i)
            if (*((SmallCube*)getChild(v[i]))->selected())
                ((SmallCube*)getChild(v[i]))->set_spin_ang(ang);
}
