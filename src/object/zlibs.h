#ifndef ZLIBBB_H
#define ZLIBBB_H
#include <iostream>
#include <zlib.h>
#include <string>
#include <cstddef>

namespace git {

class ZlibCompressor {
public:
    ZlibCompressor(const unsigned char* data, std::size_t len);
    int Read(unsigned char* msg, int len);
    std::size_t Length() const {return len_;}
private:
    const unsigned char* data_;
    std::size_t len_;
    std::size_t compressed_len_;
};

class ZlibUnCompressor {
public:
    ZlibUnCompressor(const unsigned char* data, std::size_t len);
    int Read(unsigned char* msg, int len);
    std::size_t Length() const {return len_;}
private:
    const unsigned char* data_;
    std::size_t len_;
    std::size_t compressed_len_;
};

//  if(uncompress(ubuf, &ulen, fbuf, flen) != Z_OK)
//{
//    printf("Uncompress %s failed!\n", argv[1]);
//    return -1;
//}




} //namespace
#endif // ZLIBBB_H
