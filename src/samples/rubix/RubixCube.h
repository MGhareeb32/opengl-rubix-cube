#ifndef RUBIXCUBE_H_
#define RUBIXCUBE_H_

#include "../../game/Game.h"
#include "SmallCube.h"

class RubixCube : public game::MeshEntity {
    game::Mesh *rubix, *flat;
public:
    RubixCube();
    ~RubixCube();
    void update();
    void select(int axis, GLfloat n);
    void spin(GLfloat ang);
};

#endif
