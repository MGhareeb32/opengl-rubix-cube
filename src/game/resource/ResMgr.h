#ifndef RESMGR_H_
#define RESMGR_H_

#include <map>
#include <string>
#include <iostream>
#include "../internal.h"
#include "Resource.h"
#include "ObjLoader.h"
#include "MtlLoader.h"

namespace game {
namespace ResMgr {

Resource* load(std::string file);
void unload(Resource* r);

}
}

#endif
