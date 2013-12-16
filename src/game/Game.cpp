#include "Game.h"

namespace game {

GLboolean mouse_down_[3], mouse_click_[3];
glm::vec2 mouse_pos_, mouse_pos_prev_;
GLboolean key_down_[256], key_click_[256];
GLint global_time_;

GLint unifrom_model_matrix_, unifrom_view_matrix_;
GLint unifrom_fog_color_, unifrom_fog_mag_;
GLint unifrom_blend_color_, unifrom_blend_factor_;

game::Entity* scene_;
game::Camera* camera_;

std::ostream &operator<<(std::ostream &out, const glm::vec2 &vec) {
    out << std::fixed << "(" << vec.x << " " << vec.y << ")";
    return out;
}

std::ostream &operator<<(std::ostream &out, const glm::vec3 &vec) {
    out << std::fixed << "(" << vec.x << " " << vec.y << " " << vec.z << ")";
    return out;
}

std::ostream &operator<<(std::ostream &out, const glm::vec4 &vec) {
    out << std::fixed << "(" << vec.x << " " << vec.y << " " << vec.z << " "
            << vec.w << ")";
    return out;
}

// OPENGL

void init() {
    // shader program
    GLuint program = Angel::InitShader("glsl/vshader.glsl",
                                       "glsl/fshader.glsl");
    glUseProgram(program);
    // uniform mat4 model;
    unifrom_model_matrix_ = glGetUniformLocation(program, "model");
    // uniform mat4 view;
    unifrom_view_matrix_ = glGetUniformLocation(program, "view");
    // uniform vec4 fog_color;
    unifrom_fog_color_ = glGetUniformLocation(program, "fog_color");
    // uniform float fog_mag;
    unifrom_fog_mag_ = glGetUniformLocation(program, "fog_mag");
    // uniform glm::vec3 blend_color;
    unifrom_blend_color_ = glGetUniformLocation(program, "blend_color");
    // uniform glm::vec3 blend_factor;
    unifrom_blend_factor_ = glGetUniformLocation(program, "blend_factor");

    // controls
    for (int i = 0; i < 3; ++i)
        mouse_down_[i] = mouse_click_[i] = 0;
    for (int i = 0; i < 256; ++i)
        key_down_[i] = key_click_[i] = 0;
    global_time_ = 0;

    glClearColor(.2f, .2f, .2f, 1.f);
    glClearDepth(1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    setUniformModelMatrix(glm::mat4(1));
    setUniformViewMatrix(glm::mat4(1));
    setUniformFog(glm::vec4(0.f, 0.f, 0.f, 1.f), 2.f);
}

// INPUT

void keyPress(unsigned char key, GLint x, GLint y) {
    key_down_[key] = 1;
}

void keyRelease(unsigned char key, GLint x, GLint y) {
    key_down_[key] = 0;
    key_click_[key] = 1;
}

void mouseMove(GLint x, GLint y) {
    mouse_pos_.x = x;
    mouse_pos_.y = y;
}

void mouseButton(GLint mouseBtn, GLint isRelease, GLint x, GLint y) {
    mouse_down_[mouseBtn] = !isRelease;
    mouse_click_[mouseBtn] = isRelease;
}


// DISPLAY

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    game::setUniformBlendColor(glm::vec4(1, 1, 1, 1),
                               glm::vec4(0.f, 0.f, 0.f, 0.f));

    if (camera_)
        setUniformViewMatrix
            (camera_->getProjectionMatrix() * camera_->getViewMatrix());
    if (scene_)
        scene_->render();

    glutSwapBuffers();
}

// UPDATE

void update() {
    if (scene_)
        scene_->update();
}

// MAIN LOOP

void runMainLoop(GLint f) {
    // update
    update();
    // draw
    glutPostRedisplay();
    // input
    for (int i = 0; i < 3; ++i)
        mouse_click_[i] = 0;
    for (int i = 0; i < 256; ++i)
        key_click_[i] = 0;
    mouse_pos_prev_ = mouse_pos_;
    // time
    global_time_++;

    glutTimerFunc(1000 / f, runMainLoop, f);
}

// INIT

void init(int argc, char **argv, GLint w, GLint h, std::string t) {
    std::cout.precision(2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(w, h);

    glutCreateWindow(t.c_str());
    glewInit();

    init();
}

void start(GLint f) {
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyRelease);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glutPassiveMotionFunc(mouseMove);

    glutTimerFunc(1000.0 / f, runMainLoop, f);
    glutMainLoop();

}

// OPENGL

void setUniformModelMatrix(glm::mat4 m) {
    glUniformMatrix4fv(unifrom_model_matrix_, 1, GL_FALSE, &m[0][0]);
}

void setUniformViewMatrix(glm::mat4 m) {
    glUniformMatrix4fv(unifrom_view_matrix_, 1, GL_FALSE, &m[0][0]);
}

void setUniformFog(glm::vec4 color, GLfloat mag) {
    glUniform4f(unifrom_fog_color_, color.x, color.y, color.z, color.w);
    glUniform1f(unifrom_fog_mag_, mag);
}

void setUniformBlendColor(glm::vec4 c, glm::vec4 b) {
    glUniform4f(unifrom_blend_color_, c.x, c.y, c.z, c.w);
    glUniform4f(unifrom_blend_factor_, b.x, b.y, b.z, b.w);
}

// SCENE

void setScene(game::Entity *scene, GLboolean destructOld) {
    if (destructOld && scene_)
        scene_->~Entity();
    scene_ = scene;
}

Entity* getScene() {
    return scene_;
}

void setCamera(game::Camera *camera, GLboolean destructOld) {
    if (destructOld && camera_)
        camera_->~Camera();
    camera_ = camera;
}

Camera* getCamera() {
    return camera_;
}

};
