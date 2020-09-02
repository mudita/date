#ifndef DATECOMMON_H
#define DATECOMMON_H

#include "date.h"

using namespace std::chrono;

using Clock = system_clock;
using TimePoint = time_point<Clock>;
using YearMonthDay =  date::year_month_day;

constexpr TimePoint TIME_POINT_INVALID = TimePoint::min();

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

inline TimePoint TimePointNow()
{
    return system_clock::now();
}

inline YearMonthDay TimePointToYearMonthDay(const TimePoint& tp)
{
    return date::year_month_day{date::floor<date::days>(tp)};
}

inline TimePoint TimePointFromYearMonthDay(const YearMonthDay& ymd)
{
    TimePoint tp;
    return tp;
}

//inline TimePoint TimePointNow()
//YearMonthDay
//auto dt13 = date::year_month_day{date::floor<date::days>(date2)};


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