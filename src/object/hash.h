#ifndef HASH_H
#define HASH_H
#include <string>
namespace git {

const char *ZERO_HASH = "0000000000000000000000000000000000000000";

class Hash {
public:
    Hash();
    explicit Hash(std::string hash);
    Hash(const char* hash, std::size_t len);

    const std::string& Hex() const;
    const std::string& Digit() const;
private:
    std::string hash_;
};

inline Hash::Hash():hash_(ZERO_HASH) {

}

inline Hash::Hash(std::string hash):
    hash_(hash)
{

}

inline Hash::Hash(const char *hash, std::size_t len):
    hash_(hash, len)
{

}

inline const std::string &Hash::Hex() const {
    return hash_;
}

const std::string &Hash::Digit() const {
    return hash_;
}




} //namespae
#endif // HASH_H
