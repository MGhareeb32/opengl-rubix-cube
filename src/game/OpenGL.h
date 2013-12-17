#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "../../include/Angel.h"

#include "../../include/glm/glm.hpp"
#include "../../include/glm/gtc/type_ptr.hpp"
#include "../../include/glm/gtx/transform.hpp"
#include "../../include/glm/gtc/quaternion.hpp"
#include "../../include/glm/gtc/matrix_transform.hpp"
#include "../../include/glm/gtx/transform2.hpp"

extern std::ostream &operator<<(std::ostream &out, const glm::vec2 &vec);
extern std::ostream &operator<<(std::ostream &out, const glm::vec3 &vec);
extern std::ostream &operator<<(std::ostream &out, const glm::vec4 &vec);
