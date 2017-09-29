#ifndef ERRORS_H
#define ERRORS_H

#include <string>

namespace git {


class Error {
public:
    Error(int what, std::string msg);
    Error(std::string msg);

    bool Ok() const;
    int What() const;
    const std::string& Message() const;
    std::string String() const;


    void SetCode(int what);
    void SetMessage(std::string msg);


    bool operator==(const Error& e) const;

    static constexpr int ok = 0;
    static constexpr int other = -1;
    static constexpr int eof = -2;

public:
    static Error Success();

private:
    int what_;
    std::string msg_;
    std::string extra_;
};


inline Error::Error(int what, std::string msg):
    what_(what),
    msg_(std::move(msg)),
    extra_()
{

}

inline Error::Error(std::string msg):
    what_(other),
    msg_(std::move(msg)),
    extra_()
{

}

inline bool Error::operator==(const Error &e) const {
    if (e.what_ != other && what_ != other) {
        if (e.what_ == what_) {
            return true;
        }
    }

    if (e.msg_ == e.msg_) {
        return true;
    }

    return false;
}

inline Error Error::Success() {
    return Error{ Error::ok, "ok" };
}

inline bool Error::Ok() const {
    return what_ == ok;
}

inline int Error::What() const {
    return what_;
}

inline const std::string &Error::Message() const {
    return msg_;
}

inline void Error::SetCode(int what) {
    what_ = what;
}

inline void Error::SetMessage(std::string msg) {
    msg_ = std::move(msg);
}

inline std::string Error::String() const {
    return "";
}

} // namespace

#endif // ERRORS_H
