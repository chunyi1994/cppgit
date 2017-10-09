#ifndef STRINGS_H
#define STRINGS_H
#include <string>
#include <assert.h>
#include <sstream>
#include <experimental/string_view>
namespace git {

inline bool HasPrefix(const std::string& s, const std::string& prefix){
    if (prefix.length() > s.length()) {
        return false;
    }
    for (std::size_t i = 0; i < prefix.length(); ++i) {
        if (s[i] != prefix[i]) {
            return false;
        }
    }
    return true;
}

typedef std::experimental::string_view StringView;
inline StringView SubView(const std::string& s, std::size_t start, std::size_t n) {
    return StringView{s.data()+start, n};
}

inline std::string& Trim(std::string &s, const std::string &cut) {
    if (s.empty()) {
        return s;
    }
    s.erase(0,s.find_first_not_of(cut));
    s.erase(s.find_last_not_of(cut) + 1);
    return s;
}

inline std::string HexToDigital(const std::string& data) {
    auto str = data;
    if (str.size() % 2 != 0)  {
        str = std::string("0") + str;
    }
    std::string result;
    result.reserve(str.length() / 2 + 1);
    std::stringstream ss;
    ss << std::hex;
    for (std::size_t i = 0; i < str.size() / 2; ++i) {
        int val = 0;
        ss << str.substr(i * 2, 2);
        ss >> val;
        result.push_back((unsigned char)val);
        ss.clear();
    }
    return result;
}

inline std::string DigitalToHex(const std::string& str) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (unsigned ch : str) {
        ss << std::setw(2) << int(ch);
    }
    return ss.str();
}

} //namespace
#endif // STRINGS_H
