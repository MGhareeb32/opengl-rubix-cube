#ifndef MESHENTITY_H_
#define MESHENTITY_H_

#include "Entity.h"

namespace game {

class MeshEntity : public Entity {
    Mesh *mesh_;
    Material *mtl_;
public:
    MeshEntity(Mesh *m = NULL) : Entity() { mesh_ = m; };
    virtual ~MeshEntity();

    Mesh* mesh() { return mesh_; }
    void set_mesh(Mesh *m) { mesh_ = m; }
    Material* mtl() { return mtl_; }
    void set_mtl(Material *mtl) { mtl_ = mtl; }

    virtual void render();
};

}

#endif
