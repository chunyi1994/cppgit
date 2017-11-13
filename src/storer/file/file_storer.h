#ifndef FILE_STORER_H
#define FILE_STORER_H

#include <vector>

#include "../storer.h"
#include "../../errors/errors.h"

namespace git {

class FileStorer : public Storer
{
public:
    static FileStorer* New(std::string path = ".");
    FileStorer(std::string path);
    virtual Error Get(Hash hash, Object* obj) const override{}
    virtual Error Save(const Object& obj) override{}


public:
    virtual std::string Head() const override{}
    virtual Error RefHash(std::string name, Hash& hash) const override{}
    virtual std::vector<std::string> Refs() const override{}

    virtual Error SetHead(std::string name) override{}
    virtual Error SetRef(std::string name, Hash& hash) override{}

private:
    std::string path_;

};

} // namespace
#endif // FILE_STORER_H
