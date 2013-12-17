#include "game/Game.h"
#include "../src/samples/rubix/RubixCube.h"
#include "../src/samples/meshviewer/MeshViewer.h"

const GLfloat DISPLAY_WIDTH = 640;
const GLfloat DISPLAY_HEIGHT = 640;
const GLfloat DISPLAY_FPS = 30;

int main(int argc, char **argv) {
    game::init(argc, argv, DISPLAY_WIDTH, DISPLAY_HEIGHT, "");
    game::sceneSet(new MeshViewer());
    game::start(DISPLAY_FPS);
    return 0;
}
