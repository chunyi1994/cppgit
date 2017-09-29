#ifndef ZLIBBB_H
#define ZLIBBB_H
#include <iostream>
#include <zlib.h>
#include <string>

namespace git {

class ZlibCompressor {
public:
    ZlibCompressor(const unsigned char* data, std::size_t len);
    int Read(unsigned char* msg, int len);
private:
    const unsigned char* data_;
    std::size_t len_;
    std::size_t compressed_len_;
};





} //namespace
#endif // ZLIBBB_H
