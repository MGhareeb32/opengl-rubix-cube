#ifndef RESOURCE_H_
#define RESOURCE_H_

namespace game {

class Resource {
    const std::string uid_;
public:
    Resource(std::string uid) : uid_(uid) {}
    virtual ~Resource() {}
    std::string uid() { return uid_; };
};

}

#endif
