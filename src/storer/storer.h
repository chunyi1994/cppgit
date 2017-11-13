#ifndef __STORER_H__
#define __STORER_H__

#include "../errors/errors.h"
#include "../object/hash.h"

namespace git {

class Object;

class ObjectStorer {
public:
    virtual Error Get(Hash hash, Object* obj) const = 0;
    virtual Error Save(const Object& obj) = 0;
};


class RepoInfoStorer {
public:
    virtual std::string Head() const = 0;
    virtual Error RefHash(std::string name, Hash& hash) const = 0;
    virtual std::vector<std::string> Refs() const = 0;

    virtual Error SetHead(std::string name) = 0;
    virtual Error SetRef(std::string name, Hash& hash) = 0;
};

class Storer :public ObjectStorer, public RepoInfoStorer {

};

} // namespace

#endif
