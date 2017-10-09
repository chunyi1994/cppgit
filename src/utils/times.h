#ifndef TIMES_H_
#define TIMES_H_
#include <stdint.h>
#include <sys/time.h>
namespace git {

constexpr int64_t kSECONDS_PER_HOUR = 60 * 60;
constexpr int64_t kSECONDS_PER_DAY = 24 * kSECONDS_PER_HOUR;
constexpr int64_t kUNIX_TO_INTERNAL = (1969*365 + 1969/4 - 1969/100 + 1969/400) * kSECONDS_PER_DAY;
constexpr int64_t kINTERNAL_TO_UNIX  = -kUNIX_TO_INTERNAL;

class Time {
public:
    explicit Time(int64_t timestamp);
    Time();

    int64_t Unix() const;
    bool IsZero() const;

public:
    static Time Now();

private:
    int64_t sec_;
};

inline Time::Time(int64_t timestamp):sec_(timestamp+kINTERNAL_TO_UNIX)
{

}

inline Time::Time():sec_(0)
{

}

inline int64_t Time::Unix() const {
    return sec_ - kINTERNAL_TO_UNIX;
}

inline bool Time::IsZero() const {
    return sec_ == 0;
}

inline Time Time::Now() {
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return Time{tv.tv_sec + kUNIX_TO_INTERNAL};
}

} //namespace

#endif
