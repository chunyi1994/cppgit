#ifndef OBJEC_H
#define OBJEC_H

#include <string>
#include <sstream>
#include <assert.h>
#include "../errors/errors.h"
#include "../vendor/sha1/sha1.h"

namespace git {

class Object {
public:
    enum Type {
        BLOB,
        COMMIT,
        TREE,
        REF_DELTA,
    };

public:
    Object(Type type, std::string content);
    Type Type() const;
    const std::string& Hash() const;

public:
    static Error Sha1Hash(const std::string& src, std::string* dest);
    static std::string TypeString(enum Type t);
private:
    enum Type type_;
    std::string content_;
    std::string hash_;
};



} // namespace

#endif // OBJEC_H
