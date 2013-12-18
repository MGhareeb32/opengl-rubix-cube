#include "ResMgr.h"

namespace game {
namespace ResMgr {

std::map<std::string, Resource*> resources_;

//std::vector<std::string> getObjMtls(std::string fname) {
//    std::fstream in;
//    in.open(fname.c_str(), std::fstream::in);
//    //
//    std::vector<std::string> out;
//    std::string type;
//    while (in >> type) {
//        if (!type.compare("mtllib")) {
//            in >> type;
//            out.push_back(type);
//        } else {
//            getline(in, type);
//        }
//    }
//    in.close();
//    return out;
//}

Resource* load(std::string file) {
    // already there
    if (resources_[file])
        return resources_[file];
    // path & extension
    std::size_t sepIdx = file.find_last_of("/\\") + 1;
    std::string dir
        = sepIdx != std::string::npos ? file.substr(0, sepIdx) : "";
    std::size_t dotIdx = file.find(".", 0) + 1;
    std::string extension
        = sepIdx != std::string::npos ?
            file.substr(dotIdx, file.size() - dotIdx) : "";
    // load
    std::cout << extension << " " << file << " ";
    std::cout << "from " << dir << std::endl;
    Resource* out = NULL;
    // OBJ
    if (!extension.compare("obj"))
        out = ObjLoader::load(file);
    // MTL
    else if (!extension.compare("mtl"))
        out = MtlLoader::load(file);
    // add to map
    resources_[out->uid()] = out;
    return out;
}

void unload(Resource* r) {
    resources_.erase(r->uid());
    r->~Resource();
}

}
}
