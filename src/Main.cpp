#include "Main.h"

const GLfloat DISPLAY_WIDTH = 1000;
const GLfloat DISPLAY_HEIGHT = 1000;
const GLfloat DISPLAY_FPS = 30;
GLint globalTime = 0;

GLboolean mouseDown[3], mouseClick[3];
glm::vec2 mousePos, mousePosPrev;
GLboolean keyDown[256], keyClick[256];
GLboolean inputFreeze = false;

GLint unifromModelMatrix, unifromViewMatrix;
GLint unifromBlendColor4f, unifromBlendFactor4f;

entity::Entity world, myEntity;
camera::Camera myCamera;

mesh::Mesh *axes, *box, *monkey, *pyramid, *rubix_face;

// INIT

void init(void) {
    // shader program
    GLuint program = Angel::InitShader("glsl/vshader.glsl", "glsl/fshader.glsl");
    glUseProgram(program);
    // uniform mat4 model;
    unifromModelMatrix = glGetUniformLocation(program, "model");
    // uniform mat4 view;
    unifromViewMatrix = glGetUniformLocation(program, "view");
    // uniform glm::vec3 blend_color;
    unifromBlendColor4f = glGetUniformLocation(program, "blend_color");
    // uniform glm::vec3 blend_factor;
    unifromBlendFactor4f = glGetUniformLocation(program, "blend_factor");

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClearDepth(1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // controls
    for (int i = 0; i < 3; ++i)
        mouseDown[i] = mouseClick[i] = 0;
    for (int i = 0; i < 256; ++i)
        keyDown[i] = keyClick[i] = 0;

    axes = objLoader::load("res/mesh/axes.obj");
    box = objLoader::load("res/mesh/box.obj");
    monkey = objLoader::load("res/mesh/monkey.obj");
    pyramid = objLoader::load("res/mesh/pyramid.obj");
    rubix_face = objLoader::load("res/mesh/rubix-cube-face.obj");
    // initialize faces
    world.set_mesh(axes);
    world.transform() = glm::scale
        (world.transform(), glm::vec3(.1f, .1f, .1f));
    // 1
    world.addChild("pyramid1", new entity::Entity(pyramid));
    world.getChild("pyramid1")->transform()
        = glm::rotate (90.f, glm::vec3(0, 1, 0))
        * world.getChild("pyramid1")->transform();
    world.getChild("pyramid1")->transform()
        = glm::translate(glm::vec3(1.f, 0.f, 0.f))
        * world.getChild("pyramid1")->transform();
    // 2
    world.addChild("pyramid2", new entity::Entity(pyramid));
    world.getChild("pyramid2")->transform()
        = glm::rotate (-90.f, glm::vec3(1, 0, 0))
        * world.getChild("pyramid2")->transform();
    world.getChild("pyramid2")->transform()
        = glm::translate(glm::vec3(0.f, 1.f, 0.f))
        * world.getChild("pyramid2")->transform();
    // 3
    world.addChild("pyramid3", new entity::Entity(pyramid));
    world.getChild("pyramid3")->transform()
        = glm::translate(glm::vec3(0.f, 0.f, 1.f))
        * world.getChild("pyramid3")->transform();
    // ground
    world.addChild("box", new entity::Entity(box));
//    translate_v(glm::vec3(.05f, .05f, -.05f, 1.f), world.getChild("box")->pos());
//    scale_v(glm::vec3(2.f, 2.f, 2.f, 1.f), world.getChild("box")->scale());
   // faces
//    world.addChild("face1", new entity::Entity(rubix_face));
//    translate_v(vec3(2.f, 0.f, 2.f), world.getChild("face1")->pos());

//    world.addChild("face2", new entity::Entity(rubix_face));
//    translate_v(vec3(0.f, 2.f, 2.f), world.getChild("face2")->pos());
    // monkey
//    myEntity.set_mesh(monkey);
//    scale_v(glm::vec3(20.f, 20.f, 20.f, 1.f), myEntity.scale());
//    rotate_m(-90, 0, myEntity.rot());
//    rotate_m(-45, 1, myEntity.rot());
    // reset camera
//    std::cout << std::endl;
//    std::cout << rotation(180, glm::vec3(1, 1, 0, 0)) * glm::vec3(1, .5, 0, 1) << std::endl;
//    std::cout << rotation(90, 0) * rotation(90, 1) * glm::vec3(1, .5, 0, 1) << std::endl;
}

// DISPLAY

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    xglSetViewMatrix(myCamera.getViewMatrix());

    glUniform4f(unifromBlendColor4f, 1, 1, 1, 1);
    glUniform4f(unifromBlendFactor4f, 0, 0, 0, 0);
    world.render();
//    myEntity.render();

    glutSwapBuffers();
}

// UPDATE

void update() {
//    rotate_m(5.f, glm::vec3(1, 0, 1, 1), glm::vec3(4, 0, 0, 1), &myEntity.getChild("box")->transform());
//    *myEntity.pos() = (myCamera.coi() * 300);

//    rotate_m(2.f, 1, world.getChild("pyramid1")->rot());
//    rotate_m(4.f, 1, world.getChild("pyramid2")->rot());
//    rotate_m(6.f, 1, world.getChild("pyramid3")->rot());

//    rotate_m(1.f, 0, world.getChild("face1")->rot());
//    rotate_m(2.f, 1, world.getChild("face1")->rot());
//    rotate_m(1.f, 0, world.getChild("face2")->rot());
//    rotate_m(2.f, 1, world.getChild("face2")->rot());

//    myCamera.pan(glm::vec3(0, 0.01, 0, 0));
//    myCamera.yaw(.5);

//    std::cout << std::fixed;
//    std::cout << myCamera.eye().x << ","
//              << myCamera.eye().y << ","
//              << myCamera.eye().z << " | ";
//    std::cout << std::endl << std::endl;
    // rotate

    bool speed = keyDown[' '];
    if (keyDown['q'])
        myCamera.rotate(+(speed * 4 + 1), 0);
    if (keyDown['a'])
        myCamera.rotate(-(speed * 4 + 1), 0);

    if (keyDown['w'])
        myCamera.rotate(+(speed * 4 + 1), 1);
    if (keyDown['s'])
        myCamera.rotate(-(speed * 4 + 1), 1);

    if (keyDown['e'])
        myCamera.rotate(+(speed * 4 + 1), 2);
    if (keyDown['d'])
        myCamera.rotate(-(speed * 4 + 1), 2);

    // pan

    if (keyDown['t'])
        myCamera.move(glm::vec3(+(speed * .04 + .01), 0, 0));
    if (keyDown['g'])
        myCamera.move(glm::vec3(-(speed * .04 + .01), 0, 0));

    if (keyDown['y'])
        myCamera.move(glm::vec3(0, +(speed * .04 + .01), 0));
    if (keyDown['h'])
        myCamera.move(glm::vec3(0, -(speed * .04 + .01), 0));

    if (keyDown['u'])
        myCamera.move(glm::vec3(0, 0, +(speed * .04 + .01)));
    if (keyDown['j'])
        myCamera.move(glm::vec3(0, 0, -(speed * .04 + .01)));
}

// INPUT

void keyPress(unsigned char key, GLint x, GLint y) {
    if (inputFreeze)
        return;
    keyDown[key] = 1;
}

void keyRelease(unsigned char key, GLint x, GLint y) {
    if (inputFreeze)
        return;
    keyDown[key] = 0;
    keyClick[key] = 1;
}

void mouseMove(GLint x, GLint y) {
    if (inputFreeze)
        return;
    mousePos.x = x;
    mousePos.y = y;
}

void mouseButton(GLint mouseBtn, GLint isRelease, GLint x, GLint y) {
    if (inputFreeze)
        return;
    mouseDown[mouseBtn] = !isRelease;
    mouseClick[mouseBtn] = isRelease;
}

// MAIN

void runMainLoop(int arg) {
    update();
    glutPostRedisplay();
    for (int i = 0; i < 3; ++i)
        mouseClick[i] = 0;
    for (int i = 0; i < 256; ++i)
        keyClick[i] = 0;
    mousePosPrev = mousePos;
    globalTime++;

    glutTimerFunc(1000 / DISPLAY_FPS, runMainLoop, arg);
}

int main(int argc, char **argv) {
    std::cout.precision(2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(DISPLAY_WIDTH, DISPLAY_HEIGHT);

    glutCreateWindow("Connect4");
    glewInit();

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyRelease);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glutPassiveMotionFunc(mouseMove);

    glutTimerFunc(1000 / DISPLAY_FPS, runMainLoop, 0);
    glutMainLoop();
    return 0;
}
