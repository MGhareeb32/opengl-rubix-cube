#ifndef MESHVIEWER_H_
#define MESHVIEWER_H_

#include "../../game/Game.h"
#include "MeshViewer.h"

class MeshViewer : public game::MeshEntity {
public:
    MeshViewer();
    ~MeshViewer();
    void update();
    void render();
};

#endif
