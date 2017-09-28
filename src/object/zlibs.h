#ifndef ZLIBBB_H
#define ZLIBBB_H

#include <zlib.h>
#include <string>

namespace git {

class ZlibCompressor {
public:
    ZlibCompressor(std::string raw);
    int Read(char* msg, int len);
private:
    std::string raw_;
    std::size_t compressed_len_;
};

inline ZlibCompressor::ZlibCompressor(std::string raw):
    raw_(std::move(raw))
  ,
    compressed_len_(compressBound(raw_.length()))
{
}

inline int ZlibCompressor::Read(char *msg, int len) {
    uLong nread = 0;
    compress((unsigned char*)msg, &nread, (const unsigned char*)raw_.data(), (uLong)raw_.length());
    return (int)nread;
}

} //namespace
#endif // ZLIBBB_H
