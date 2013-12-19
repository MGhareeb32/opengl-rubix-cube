#include "Game.h"

// OUTPUT VECTORS

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

namespace game {

GLint unifrom_model_matrix_, unifrom_view_matrix_, unifrom_proj_matrix_;

GLint unifrom_scene_color_, unifrom_scene_fog_;

const int NUM_LIGHTS = 32;
std::vector<Light*> lights;
GLint unifrom_lights_[NUM_LIGHTS];

GLint unifrom_mtl_ka_, unifrom_mtl_kd_, unifrom_mtl_ks_;
GLint unifrom_mtl_ns_, unifrom_mtl_tr_;

GLint unifrom_blend_color_, unifrom_blend_factor_;

GLboolean mouse_down_[3], mouse_click_[3];
glm::vec2 mouse_pos_, mouse_pos_prev_;
GLboolean key_down_[256], key_click_[256];
GLint global_time_;

game::Entity* scene_;
game::Camera* camera_;

// OPENGL

void setUniformModelMatrix(glm::mat4 m) {
    glUniformMatrix4fv(unifrom_model_matrix_, 1, GL_FALSE, &m[0][0]);
}

void setUniformViewMatrix(glm::mat4 m) {
    glUniformMatrix4fv(unifrom_view_matrix_, 1, GL_FALSE, &m[0][0]);
}

void setUniformProjMatrix(glm::mat4 m) {
    glUniformMatrix4fv(unifrom_proj_matrix_, 1, GL_FALSE, &m[0][0]);
}

void fogSet(glm::vec4 color, GLfloat mag) {
    glClearColor(color.x, color.y, color.z, 1.f);
    glUniform1f(unifrom_scene_fog_, mag);
}

void setUniformBlendColor(glm::vec4 c, glm::vec4 b) {
    glUniform4f(unifrom_blend_color_, c.x, c.y, c.z, c.w);
    glUniform4f(unifrom_blend_factor_, b.x, b.y, b.z, b.w);
}

// MATERIAL

void mtlSet(Material* mtl) {
    glUniform3f(unifrom_mtl_ka_, mtl->ka().x, mtl->ka().y, mtl->ka().z);
    glUniform3f(unifrom_mtl_kd_, mtl->kd().x, mtl->kd().y, mtl->kd().z);
    glUniform3f(unifrom_mtl_ks_, mtl->ks().x, mtl->ks().y, mtl->ks().z);
    glUniform1f(unifrom_mtl_ns_, mtl->ns());
    glUniform1f(unifrom_mtl_tr_, mtl->tr());
}

// LIGHT

void lightSet(int idx, Light* l) {
    glm::mat4 a = glm::mat4(glm::vec4(l->o(), 0),
                            glm::vec4(l->ambient(), 0),
                            glm::vec4(l->diffuse(), 0),
                            glm::vec4(l->specular(), 0));
    glUniformMatrix4fv(unifrom_lights_[idx], 1, GL_FALSE, &a[0][0]);
}

// SCENE

void sceneSet(game::Entity *scene, GLboolean destructOld) {
    if (destructOld && scene_)
        scene_->~Entity();
    scene_ = scene;
}

Entity* sceneGet() {
    return scene_;
}

void sceneColorSet(glm::vec3 color) {
    glUniform3f(unifrom_scene_color_, color.x, color.y, color.z);
}

// CAMERA

void cameraSet(game::Camera *camera, GLboolean destructOld) {
    if (destructOld && camera_)
        camera_->~Camera();
    camera_ = camera;
}

Camera* cameraGet() {
    return camera_;
}

// INIT

void init() {
    // shader program
    GLuint program = Angel::InitShader("glsl/vshader.glsl",
                                       "glsl/fshader.glsl");
    glUseProgram(program);
    // uniform mat4 model, view, proj;
    unifrom_model_matrix_ = glGetUniformLocation(program, "model");
    unifrom_view_matrix_ = glGetUniformLocation(program, "view");
    unifrom_proj_matrix_ = glGetUniformLocation(program, "proj");
    // uniform float scene_fog;
    // uniform vec3 scene_color;
    unifrom_scene_fog_ = glGetUniformLocation(program, "scene_fog");
    unifrom_scene_color_ = glGetUniformLocation(program, "scene_color");
    // uniform vec3 lights[NUM_LIGHTS][4];
    for (int i = 0; i < NUM_LIGHTS; ++i) {
        std::stringstream ss;
        ss << "lights[" << i << "]";
        unifrom_lights_[i] = glGetUniformLocation(program, ss.str().c_str());
        Light *l = new Light(glm::vec3(0), glm::vec3(0), glm::vec3(0));
        lightSet(i, l);
        l->~Light();
    }
    // uniform vec3 ka, kd, ks;
    unifrom_mtl_ka_ = glGetUniformLocation(program, "ka");
    unifrom_mtl_kd_ = glGetUniformLocation(program, "kd");
    unifrom_mtl_ks_ = glGetUniformLocation(program, "ks");
    // uniform float ns, tr;
    unifrom_mtl_ns_ = glGetUniformLocation(program, "ns");
    unifrom_mtl_tr_ = glGetUniformLocation(program, "tr");
    // uniform glm::vec3 blend_color;
    unifrom_blend_color_ = glGetUniformLocation(program, "blend_color");
    // uniform glm::vec3 blend_factor;
    unifrom_blend_factor_ = glGetUniformLocation(program, "blend_factor");
    std::cout << "uniforms loaded" << std::endl;

    // controls
    for (int i = 0; i < 3; ++i)
        mouse_down_[i] = mouse_click_[i] = 0;
    for (int i = 0; i < 256; ++i)
        key_down_[i] = key_click_[i] = 0;
    global_time_ = 0;

    glClearDepth(1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    setUniformModelMatrix(glm::mat4(1));
    setUniformViewMatrix(glm::mat4(1));
    setUniformProjMatrix(glm::mat4(1));
    mtlSet(new Material("default"));
    sceneColorSet(glm::vec3(0.1f, 0.1f, 0.1f));
    fogSet(glm::vec4(0.1f, 0.1f, 0.1f, 1.f), 1.f);
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
        setUniformViewMatrix(camera_->getViewMatrix()),
        setUniformProjMatrix(camera_->getProjectionMatrix());
    for (int i = 0; i < lights.size(); ++i)
        lightSet(i, lights[i]);
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

};
