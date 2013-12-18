#include "MeshViewer.h"

MeshViewer::MeshViewer() {
    cam_ = new game::Camera();
    game::cameraSet(cam_);
    // load
    obj_mesh_ = (game::Mesh*)game::ResMgr::load("res/mesh/teapot.obj");
    obj_mtl_ = (game::Material*)game::ResMgr::load("res/mesh/teapot.mtl");
    axes_mesh_ = (game::Mesh*)game::ResMgr::load("res/mesh/axes.obj");
    axes_mtl_ = (game::Material*)game::ResMgr::load("res/mesh/axes.mtl");
    light_mesh_ = (game::Mesh*)game::ResMgr::load("res/mesh/box.obj");
    light_mtl_ = (game::Material*)game::ResMgr::load("res/mesh/box.mtl");
    // axes
    set_mesh(axes_mesh_);
    set_mtl(axes_mtl_);
    // obj
    obj_entity_ = new game::MeshEntity(obj_mesh_);
    obj_entity_->set_mtl(obj_mtl_);
    addChild("obj", obj_entity_);
    obj_entity_->scale(glm::vec3(.5f, .5f, .5f));
    // light
    light_entity_ = new game::MeshEntity(light_mesh_);
    light_entity_->set_mtl(light_mtl_);
    addChild("light", light_entity_);
    light_entity_->addChild("light", game::lightGet());
    light_entity_->scale(glm::vec3(.1f, .1f, .1f));
    light_entity_->translate(glm::vec3(1, 0, 0));
}

MeshViewer::~MeshViewer() {
}

void MeshViewer::update() {
    GLfloat speed = game::key_down_[' '] * 3 + 2;
    // obj
    if (game::key_down_['x'])
        obj_entity_->rotate(+speed, glm::vec3(0, 0, 1), glm::vec3(0, 0, 0));
    if (game::key_down_['z'])
        obj_entity_->rotate(-speed, glm::vec3(0, 0, 1), glm::vec3(0, 0, 0));
    // light
    if (game::key_down_['c'])
        light_entity_->rotate(+speed, glm::vec3(0, 0, 1), glm::vec3(0, 0, 0));
    if (game::key_down_['v'])
        light_entity_->rotate(-speed, glm::vec3(0, 0, 1), glm::vec3(0, 0, 0));
    // camera
    game::Camera* myCamera = game::cameraGet();
    if (game::key_down_['w'])
        myCamera->rotate(+speed, myCamera->u());
    if (game::key_down_['s'])
        myCamera->rotate(-speed, myCamera->u());

    if (game::key_down_['q'])
        myCamera->rotate(+speed, myCamera->n());
    if (game::key_down_['e'])
        myCamera->rotate(-speed, myCamera->n());

    if (game::key_down_['d'])
        myCamera->rotate(+speed, glm::vec3(0, 0, 1));
    if (game::key_down_['a'])
        myCamera->rotate(-speed, glm::vec3(0, 0, 1));

    if (game::key_down_['A'])
        myCamera->translate(-myCamera->u() * .1f);
    if (game::key_down_['D'])
        myCamera->translate(myCamera->u() * .1f);
}
