#ifndef COMMIT_H
#define COMMIT_H
#include <string>
namespace git {

class Commit {
    static Commit Marshal(const char *content, std::size_t len);
};


} // namespace

#endif // COMMIT_H
