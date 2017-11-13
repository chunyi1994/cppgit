#ifndef BRANCH_H
#define BRANCH_H
#include <string>
#include <memory>
#include "../storer/storer.h"
#include "../object/hash.h"

namespace git {

class Branch {
public:
    Branch();
    const git::Hash& Hash() const { return hash_; }
    Error SetHash(git::Hash hash) const;

private:
    git::Hash hash_;
    std::string name_;
    std::shared_ptr<Storer> storer_;
};


} // namespace

#endif // BRANCH_H
