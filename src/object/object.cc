
#include "object.h"

namespace git {

Object::Object(enum Type type, std::string content):
    type_(type),
    content_(content),
    hash_()
{
    std::stringstream ss;
    ss << TypeString(type_) ;
    ss << " ";
    ss << content_.length();
    ss << '\0';
    CSHA1 sha1;
    auto header = ss.str();
    sha1.Update((const unsigned char*)header.data(),header.length());
    sha1.Update((const unsigned char*)content_.data(),content_.length());
    sha1.Final();
    sha1.ReportHashStl(hash_, CSHA1::REPORT_HEX_SHORT);
}

enum Object::Type Object::Type() const {
    return type_;
}

const std::string &Object::Hash() const {
    return hash_;
}

Error Object::Sha1Hash(const std::string& src, std::string* dest) {
    assert(dest != nullptr);
    CSHA1 sha1;
    sha1.Update((const unsigned char*)src.data(),src.length());
    sha1.Final();
    std::string hash;
    if (!sha1.ReportHashStl(hash, CSHA1::REPORT_HEX_SHORT)) {
        return Error{"sha1: bad content"};
    }
    dest->swap(hash);
    return Error::Success();
}

std::string Object::TypeString(enum Object::Type t) {
    switch (t) {
    case BLOB:
        return "blob";
    case COMMIT:
        return "commit";
    case TREE:
        return "tree";
    case REF_DELTA:
        return "ref-delta";
    default:
        return "unknown";
    }
}

} //namespace
