#ifndef MESH_H_
#define MESH_H_

#include "Face.h"
#include "Internal.h"

namespace game {

class Mesh {
	std::vector<Face *> faces;
public:
	Mesh();
	void addFace(Face *f) { faces.push_back(f); }
    void render(glm::mat4 transformation);
	virtual ~Mesh();
};

Mesh *new_pyramid();

}

#endif
