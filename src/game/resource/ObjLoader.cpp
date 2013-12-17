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
    game::Material *mtl = NULL;
    std::string type;
    while (in >> type) {
        if (!type.compare("v")) {
            glm::vec3 v;
            in >> v.x >> v.z >> v.y;
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
            mtl = (Material*)ObjLoader::load(type);
        } else if (!type.compare("f")) {
            glm::vec4 c[3];
            glm::vec3 v[3], vn[3];
            int a[4];
            char d;
            for (int i = 0; i < 3; ++i) {
                // v/vt/vn
                // coord
                if (vertex.size())
                    in >> a[0];
                v[i] = vertex[a[0] - 1];
                // vt TODO
                in >> d;
                if (uvmap.size())
                    in >> a[1];
                // normal
                in >> d;
                if (normal.size())
                    in >> a[2];
                vn[i] = normal[a[2] - 1];
                // color
                if (color.size())
                    in >> d >> a[3], c[i] = color[a[3] - 1];
                else
                    c[i] = glm::vec4(1.0,
                                     1.0,
                                     1.0, 1.f);
            }
            out->addFace(new Face(3, v, vn, c, GL_TRIANGLES));
        } else {
            getline(in, type);
        }
    }
    in.close();
    out->set_mtl(mtl);
    return out;
}

}
}
