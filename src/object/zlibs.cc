#include "zlibs.h"

namespace git {

ZlibCompressor::ZlibCompressor(const unsigned char *data, std::size_t len):
    data_(data), len_(len)
  ,
    compressed_len_(compressBound(len))
{
}

int ZlibCompressor::Read(unsigned char *msg, int len) {
    uLong nread = len;
    //    compress returns Z_OK if success, Z_MEM_ERROR if there was not
    //  enough memory, Z_BUF_ERROR if there was not enough room in the output
    //  buffer.
    int err = compress2(msg,
                        &nread,
                        data_,
                        len_,9);

    switch (err) {
    case Z_OK:
        std::cout<<"Z_OK"<<std::endl;
        break;
    case Z_BUF_ERROR:
        std::cout<<"Z_BUF_ERROR"<<std::endl;
        break;
    case Z_MEM_ERROR:
        std::cout<<"Z_MEM_ERROR"<<std::endl;
        break;
    default:
        std::cout<<"other:"<<err<<std::endl;
        break;
    }
    return (int)nread;
}

ZlibUnCompressor::ZlibUnCompressor(const unsigned char *data, std::size_t len):
    data_(data), len_(len)
,
  compressed_len_(len)
{

}

int ZlibUnCompressor::Read(unsigned char *msg, int len)
{
    uLong nread = len;
    int err = uncompress(msg,
                        &nread,
                        data_,
                        len_);

    switch (err) {
    case Z_OK:
        std::cout<<"Z_OK"<<std::endl;
        break;
    case Z_BUF_ERROR:
        std::cout<<"Z_BUF_ERROR"<<std::endl;
        break;
    case Z_MEM_ERROR:
        std::cout<<"Z_MEM_ERROR"<<std::endl;
        break;
    default:
        std::cout<<"other:"<<err<<std::endl;
        break;
    }
    return (int)nread;
}

} // namespace
