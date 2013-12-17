#include "ObjLoader.h"

namespace game {
namespace ObjLoader {

game::Mesh *load(std::string fname) {
    std::fstream in;
    in.open(fname.c_str(), std::fstream::in);
    std::cout << fname << " open" << std::endl << "    ";
    //
    std::vector<glm::vec4> color;
    std::vector<glm::vec3> vertex, normal;
    std::vector<glm::vec2> uvmap;
    game::Mesh *out = new game::Mesh();
    std::string type;
    while (in >> type) {
//        std::cout << type << " ";
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
        } else if (!type.compare("f")) {
            glm::vec4 c[3];
            glm::vec3 v[3], vn[3];
            int a[4];
            char d;
            for (int i = 0; i < 3; ++i) {
                // v/vt/vn
                if (vertex.size())
                    in >> a[0];
                in >> d;
                if (uvmap.size())
                    in >> a[1];
                in >> d;
                if (normal.size())
                    in >> a[2];
                // coord
                v[i] = vertex[a[0] - 1];
                // normal
                vn[i] = normal[a[0] - 1];
                // color
                if (color.size())
                    in >> d >> a[3], c[i] = color[a[3] - 1];
                else
                    c[i] = glm::vec4((rand() % 100) / 100.0,
                                     (rand() % 100) / 100.0,
                                     (rand() % 100) / 100.0, 1.f);
                // TODO uvmap, normal
            }
            out->addFace(new Face(3, v, vn, c, GL_TRIANGLES));
        } else {
//			cout << "faketh";
            getline(in, type);
        }
//		cout << endl;
    }
    std::cout << "vertices=" << vertex.size() << " ";
    std::cout << "normals=" << normal.size() << " ";
    std::cout << "uvmaps=" << uvmap.size() << " ";
    std::cout << "colors=" << color.size() << " ";
    in.close();
//    cout << type << " ";

    std::cout << std::endl << "   closed" << std::endl;
    return out;
}

}
}
