#ifndef BUFFER_H
#define BUFFER_H
#include <vector>
namespace git {

class Buffer {
public:

private:
    std::vector<char> buf_;
};


class Bytes {
public:
    template<int N>
    Bytes(const char (&arr)[N]);

    std::size_t Length() const { return len_; }
    const char* Data() const { return data_; }
private:
    const char* data_;
    std::size_t len_;
};

template<int N>
inline Bytes::Bytes(const char (&arr)[N]):
    data_(arr), len_(N)
{
}

} // namespace

#endif // BUFFER_H
