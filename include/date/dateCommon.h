#ifndef DATECOMMON_H
#define DATECOMMON_H

#include "date.h"

using namespace std::chrono;

using Clock = system_clock;
using TimePoint = time_point<Clock>;
using YearMonthDay =  date::year_month_day;

constexpr TimePoint TIME_POINT_INVALID = TimePoint::min();


inline std::tm CreateTmStruct(int year, int month, int day, int hour, int minutes, int seconds)
{
    struct tm tm_ret;

    tm_ret.tm_isdst = -1;
    tm_ret.tm_sec = seconds;
    tm_ret.tm_min = minutes;
    tm_ret.tm_hour = hour;
    tm_ret.tm_mday = day;
    tm_ret.tm_mon = month - 1;
    tm_ret.tm_year = year - 1900;

    return tm_ret;
}

inline time_t GetDiffLocalWithUTCTime()
{
    std::tm tm = CreateTmStruct(2000, 1, 1, 0, 0, 0);

    std::time_t basetime = std::mktime( &tm );
    std::time_t diff;

    tm = *std::localtime( &basetime );
    tm.tm_isdst = -1;
    diff = std::mktime( &tm );

    tm = *std::gmtime( &basetime );
    tm.tm_isdst = -1;
    diff -= std::mktime( &tm );

    return diff;
}

inline time_t GetAsUTCTime(int year, int month, int day, int hour = 0, int minutes = 0, int seconds = 0)
{
    std::tm tm = CreateTmStruct(year, month, day, hour, minutes, seconds);
    std::time_t basetime = std::mktime( &tm );

    return basetime + GetDiffLocalWithUTCTime();
}

inline TimePoint TimePointNow()
{
    return system_clock::now();
}

inline std::string TimePointToString(const TimePoint& tp)
{
    return date::format("%F %T", time_point_cast<seconds>(tp));
}

inline TimePoint TimePointFromString(const char* s1)
{
    TimePoint tp;
    std::istringstream(s1) >> date::parse("%F %T", tp);
    return tp;
}

inline TimePoint TimePointFromTimeT(const time_t& time)
{
    return system_clock::from_time_t(time);
}

inline time_t TimePointToTimeT(const TimePoint& tp)
{
    return system_clock::to_time_t(tp);
}

inline YearMonthDay TimePointToYearMonthDay(const TimePoint& tp)
{
    return date::year_month_day{date::floor<date::days>(tp)};
}

inline TimePoint TimePointFromYearMonthDay(const YearMonthDay& ymd)
{
    return date::sys_days{ymd.year() / ymd.month() / ymd.day()};
}

inline auto TimePointToHourMinSec(const TimePoint& tp)
{
    auto dp = date::floor<date::days>(tp);
    return date::make_time(tp - dp);
}



#if 0
class _TimePoint : public TimePoint
{
  public:
    _TimePoint(){};

    std::string ToString()
    {
        return date::format("%F %T", time_point_cast<seconds>(*this));
    }

    void FromString(const char* s1)
    {
        std::istringstream(s1) >> date::parse("%F %T", *this);
    }

    /*_TimePoint operator=(const char* s1)
    {
        _TimePoint tp;
        std::istringstream(s1) >> date::parse("%F %T", tp);
        return tp;
    }*/
};
#endif

#endif  // DATECOMMON_H