#include "ObjLoader.h"

namespace game {
namespace ObjLoader {

game::Mesh *load(std::string fname) {
    std::fstream in;
    in.open(fname.c_str(), std::fstream::in);
    //
    std::vector<glm::vec4> color;
    std::vector<glm::vec3> vertex, normal;
    std::vector<glm::vec2> uvmap;
    game::Mesh *out = new game::Mesh(fname);
    std::string type;
    while (in >> type) {
        if (!type.compare("v")) {
            glm::vec3 v;
            in >> v.x >> v.y >> v.z;
            vertex.push_back(v);
        } else if (!type.compare("vt")) {
            glm::vec2 vt;
            in >> vt.x >> vt.y;
            uvmap.push_back(vt);
        } else if (!type.compare("vn")) {
            glm::vec3 vn;
            in >> vn.x >> vn.y >> vn.z;
            normal.push_back(vn);
        } else if (!type.compare("c")) {
            glm::vec4 c;
            in >> c.x >> c.y >> c.z >> c.w;
            color.push_back(c);
        } else if (!type.compare("mtllib")) {
            in >> type;
        } else if (!type.compare("f")) {
            glm::vec4 c[3];
            glm::vec3 v[3], vn[3];
            int a;
            char d;
            for (int i = 0; i < 3; ++i) {
                // v/vt/vn
                // coord
                if (vertex.size())
                    in >> a;
                v[i] = vertex[a - 1];
                // vt TODO
                in >> d;
                if (uvmap.size())
                    in >> a;
                // normal
                in >> d;
                if (normal.size())
                    in >> a;
                vn[i] = normal[a - 1];
                // color
                if (color.size())
                    in >> d >> a, c[i] = color[a - 1];
                else
                    c[i] = glm::vec4(1.0,
                                     1.0,
                                     1.0, 1.f);
            }
            out->addFace(new Face(3, v, vn, c, GL_TRIANGLE_STRIP));
        } else {
            getline(in, type);
        }
    }
    in.close();
    return out;
}

}
}
