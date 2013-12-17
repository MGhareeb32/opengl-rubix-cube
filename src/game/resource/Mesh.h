#ifndef MESH_H_
#define MESH_H_

#include "Face.h"
#include "../Internal.h"
#include "Resource.h"

namespace game{

class Mesh : public Resource {
    std::vector<Face *> faces;
public:
	Mesh(std::string uid);
	void addFace(Face *f) { faces.push_back(f); }
    void render(glm::mat4 transformation);
	virtual ~Mesh();
};

Mesh *new_pyramid();

}

#endif
