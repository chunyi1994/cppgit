#include "hash.h"

namespace git {

Hash::Hash():hash_(ZERO_HASH) {

}

Hash::Hash(std::string hash):
    hash_(hash)
{

}

Hash::Hash(const char *hash, std::size_t len):
    hash_(hash, len)
{

}

const std::string &Hash::Hex() const {
    return hash_;
}

const std::string &Hash::Digit() const {
    return hash_;
}

} //namespace
