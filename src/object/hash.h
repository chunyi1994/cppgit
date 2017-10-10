#ifndef HASH_H
#define HASH_H
#include <string>
namespace git {

static const char *ZERO_HASH = "0000000000000000000000000000000000000000";

class Hash {
public:
    Hash();
    explicit Hash(std::string hash);
    Hash(const char* hash, std::size_t len);

    void Set(std::string hash) { hash_ = hash; }

    const std::string& Hex() const;
    const std::string& Digit() const;
private:
    std::string hash_;
};

} //namespae
#endif // HASH_H
