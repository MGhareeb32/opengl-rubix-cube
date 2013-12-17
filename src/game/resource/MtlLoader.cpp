#include "MtlLoader.h"

namespace game {
namespace MtlLoader {

Material *load(std::string fname) {
    std::fstream in;
    in.open(fname.c_str(), std::fstream::in);
    //
    GLfloat ns, ni, tr, lum;
    glm::vec3 ka, kd, ks;
    std::string type;
    while (in >> type) {
        if (!type.compare("Ns")) {
            in >> ns;
        } else if (!type.compare("Ka")) {
            in >> ka.x >> ka.y >> ka.z;
        } else if (!type.compare("Kd")) {
            in >> kd.x >> kd.y >> kd.z;
        } else if (!type.compare("Ks")) {
            in >> ks.x >> ks.y >> ks.z;
        } else if (!type.compare("Ni")) {
            in >> ni;
        } else if (!type.compare("Tr") || !type.compare("d")) {
            in >> tr;
        } else if (!type.compare("illum")) {
            in >> lum;
        } else {
            getline(in, type);
        }
    }
    in.close();
    return new Material(fname, ka, kd, ks, ns, tr);
}

}
}
