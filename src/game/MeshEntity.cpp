#include "MeshEntity.h"

namespace game {

MeshEntity::~MeshEntity() {
}

void MeshEntity::render() {
    // render self
    if (mesh_)
        mesh_->render(transform());
    // super implementation
    Entity::render();
}

}
