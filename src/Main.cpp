#include "Main.h"

const GLfloat WindowWidth = 600;
const GLfloat WindowHeight = 600;
const GLfloat screenFps = 30;
GLint globalTime = 0;

GLboolean mouseDown[3], mouseClick[3];
vec2 mousePos, mousePosPrev;
GLboolean keyDown[256], keyClick[256];

GLint unifromOffset2f, unifromScale2f;
GLint unifromBlendColor4f, unifromBlendFactor4f;

C4Game game;
GLint gameSelectedCol, gameSelectedRow;
GLfloat cellS = 2.f / (game.W > game.H ? (game.W + 1) : (game.H + 1));
Polygon2D *polygonSquare, *polygonCircle, *polygonArrow;
rgba backgroundCol;

// INIT

void init(void) {
    // shader program
    GLuint program = InitShader("glsl/vshader.glsl", "glsl/fshader.glsl");
    glUseProgram(program);
    // uniform vec2 offset;
    unifromOffset2f = glGetUniformLocation(program, "offset");
    // uniform vec2 scale;
    unifromScale2f = glGetUniformLocation(program, "scale");
    // uniform vec4 blend_color;
    unifromBlendColor4f = glGetUniformLocation(program, "blend_color");
    // uniform vec4 blend_factor;
    unifromBlendFactor4f = glGetUniformLocation(program, "blend_factor");

    // blend
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // controls
    for (int i = 0; i < 3; ++i)
        mouseDown[i] = mouseClick[i] = 0;
    for (int i = 0; i < 256; ++i)
        keyDown[i] = keyClick[i] = 0;

    // initialize polygons
    polygonSquare = new_square(rgba(1.0, 1.0, 1.0, 0.8));
    polygonCircle = new_circle(rgba(1.0, 1.0, 1.0, 0.8), 16);
    polygonArrow = new_arrow(rgba(1.0, 1.0, 1.0, 0.8));
    gameSelectedCol = 0;
    gameSelectedRow = -1;
}

// DISPLAY

void display(void) {
    // background
    glUniform2f(unifromOffset2f, 0.0, 0.0);
    glUniform2f(unifromScale2f, 2.0, 2.0);
    glUniform4f(unifromBlendColor4f,
                backgroundCol.x, backgroundCol.y, backgroundCol.z,
                backgroundCol.w);
    glUniform4f(unifromBlendFactor4f, 1.0, 1.0, 1.0, 1.0);
    polygonSquare->render();
    // horizontal bars
    glUniform2f(unifromScale2f, 2.0, 0.1);
    glUniform4f(unifromBlendFactor4f, 0.98, 0.98, 0.98, 1.0);
    for (int i = 0; i < 5; ++i) {
        glUniform2f(unifromOffset2f, 0.0, (((globalTime + 40 * i) % 200) * 0.01) - 1.0);
        polygonSquare->render();
    }
    // board
    for (GLint i = game.H - 1; i >= 0; --i) {
        for (GLint j = 0; j < game.W; ++j) {
            // position
            GLint x =  j - game.W / 2, y = i - game.H / 2 + 1;
            // bg
            glUniform2f(unifromScale2f, cellS, cellS);
            glUniform4f(unifromBlendColor4f,
                        0.0, 0.1 + 0.03 * (game.H - i), 0.4 + 0.05 * j, 0.0);
            glUniform4f(unifromBlendFactor4f, 1.0, 1.0, 1.0, 0.0);
            glUniform2f(unifromOffset2f, x * cellS, (y - 0.05) * cellS);
            polygonSquare->render();

            glUniform4f(unifromBlendFactor4f, 0.8, 0.8, 0.8, 0.0);
            glUniform2f(unifromOffset2f, x * cellS, (y + 0.05) * cellS);
            glUniform2f(unifromOffset2f, x * cellS, y * cellS);
            polygonSquare->render();
            glUniform2f(unifromOffset2f, x * cellS, y * cellS);
            // hole
            glUniform2f(unifromScale2f, cellS * 0.8, cellS * 0.8);
            glUniform4f(unifromBlendColor4f, 0.0, 0.0, 0.4, 0.2);
            glUniform4f(unifromBlendFactor4f, 1.0, 1.0, 1.0, 1.0);
            polygonCircle->render();
            // disc
            if (game[i][j] == 0) {
                glUniform4f(unifromBlendColor4f, 0.0, 0.0, 0.0, 0.2);
                glUniform2f(unifromScale2f, cellS * 0.65, cellS * 0.65);
                polygonCircle->render();
            } else {
                bool player2 = game[i][j] - 1;

                glUniform4f(unifromBlendFactor4f, 1.0, 1.0, 1.0, 1.0);
                glUniform4f(unifromBlendColor4f,
                            0.8 * !player2, 0.6 * player2, 0.1, 1.0);
                glUniform2f(unifromScale2f, cellS * 0.7, cellS * 0.7);
                polygonCircle->render();

                glUniform4f(unifromBlendColor4f,
                            0.9 * !player2, 0.7 * player2, 0.1, 1.0);
                glUniform2f(unifromScale2f, cellS * 0.6, cellS * 0.6);
                polygonCircle->render();
            }
        }
    }
    // indicator
    if (!game.getWinner()) {
        bool player2 = game.getCurrentPlayer() == 2;
        GLfloat x = -game.W / 2 + gameSelectedCol;
        GLfloat y = -game.H / 2 + sin(globalTime * 0.2) * 0.05;

        glUniform4f(unifromBlendFactor4f, 1.0, 1.0, 1.0, 1.0);
        glUniform4f(unifromBlendColor4f,
                    0.9 * !player2, 0.7 * player2, 0.1, 0.8);
        glUniform2f(unifromScale2f, cellS * 0.7, -cellS * 0.5);
        glUniform2f(unifromOffset2f, x * cellS, y * cellS);
        polygonArrow->render();

        glUniform2f(unifromOffset2f, x * cellS, (y + 0.05) * cellS);
        polygonArrow->render();
    }
    // scores
    for (int i = 0; i < game.getScore(1) + game.getScore(2); ++i) {
        bool player2 = game.getScore(1) < i + 1;
        GLfloat x = i - (game.getScore(1) + game.getScore(2)) / 2;
        GLfloat y = -game.H / 2 - 0.8;

        glUniform4f(unifromBlendFactor4f, 1.0, 1.0, 1.0, 1.0);
        glUniform4f(unifromBlendColor4f,
                    0.9 * !player2, 0.7 * player2, 0.1, 0.8);
        glUniform2f(unifromScale2f, cellS * 0.2, -cellS * 0.2);
        glUniform2f(unifromOffset2f, x * cellS, y * cellS);
        polygonSquare->render();

        glUniform2f(unifromOffset2f, x * cellS, (y + 0.05) * cellS);
        polygonSquare->render();
    }
    glFlush();
}

// UPDATE

void update() {
    GLint winner = game.getWinner();
    // still playing
    if (!winner) {
        backgroundCol = rgba(0.0, 0.0, 0.0, 0.3);
        GLint hoveredCol
            = -(mousePos.x - (1 - cellS * game.W / 2) * WindowHeight)
            / (WindowWidth / game.W) - 2;
        if (keyClick['d'])
            gameSelectedCol--;
        else if (keyClick['a'])
            gameSelectedCol++;
        else if (keyClick['s'])
            game.play(gameSelectedCol);
        else if (abs(mousePos.x - mousePosPrev.x) > WindowWidth / 100)
            gameSelectedCol = hoveredCol;
        else if (mouseClick[0])
            game.play(gameSelectedCol);
        gameSelectedCol += game.W;
        gameSelectedCol %= game.W;
    }
    // end
    else {
        if (game.getScore(1) + game.getScore(2) >= game.SCORE) {
            game.resetScore();
            backgroundCol = rgba(1.0, 1.0, 1.0, 0.3);
        } else if (winner != -1) {
            bool player2 = (winner == 2);
            backgroundCol = rgba(0.5 * !player2, 0.5 * player2, 0.0, 0.3);
        } else {
            backgroundCol = rgba(0.3, 0.0, 0.3, 0.1);
        }
        bool anyPressed = mouseClick[0];
        for (int i = 0; i < 256 && !anyPressed; ++i)
            anyPressed = keyClick[i];
        if (anyPressed)
            game.init();
    }
}

// INPUT

void keyPress(unsigned char key, GLint x, GLint y) {
    keyDown[key] = 1;
}

void keyRelease(unsigned char key, GLint x, GLint y) {
    keyDown[key] = 0;
    keyClick[key] = 1;
}

void mouseMove(GLint x, GLint y) {
    mousePos.x = x;
    mousePos.y = y;
}

void mouseButton(GLint mouseBtn, GLint isRelease, GLint x, GLint y) {
    mouseDown[mouseBtn] = !isRelease;
    mouseClick[mouseBtn] = isRelease;
}

// MAIN

void runMainLoop(int arg) {
    update();
    display();
    for (int i = 0; i < 3; ++i)
        mouseClick[i] = 0;
    for (int i = 0; i < 256; ++i)
        keyClick[i] = 0;
    mousePosPrev = mousePos;
    globalTime++;

    glutTimerFunc(1000 / screenFps, runMainLoop, arg);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(WindowWidth, WindowHeight);

    glutCreateWindow("Connect4");
    glewInit();

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyRelease);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glutPassiveMotionFunc(mouseMove);

    glutTimerFunc(1000 / screenFps, runMainLoop, 0);
    glutMainLoop();
    return 0;
}
