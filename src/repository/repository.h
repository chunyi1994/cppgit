#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include <memory>
#include <string>

#include "../object/hash.h"
#include "../errors/errors.h"
#include "../storer/storer.h"

namespace git {



class Repository {
public:
    static Error Create(std::string name, std::shared_ptr<Storer> s, Repository* r);
private:
    std::shared_ptr<Storer> storer_;
    std::string name_;
};

}

#endif
