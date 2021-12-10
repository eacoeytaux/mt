#ifndef SysTime_hpp
#define SysTime_hpp

#include "SysIncludes.hpp"

namespace mt {
    class SysTime {
    public:
        SysTime();
        SysTime(std::uint64_t ms);
        
        std::uint64_t total_ms() const;
        
        std::uint64_t seconds() const;
        std::uint64_t minutes() const;
        std::uint64_t hours() const;
        
        string timestamp(string delim = ":") const;
        string datestamp(string delim = "-") const;
        
        SysTime operator+(const SysTime & t) const;
        SysTime & operator+=(const SysTime & t);
        SysTime operator-(const SysTime & t) const;
        SysTime & operator-=(const SysTime & t);
        
    private:
        uint64_t m_ms;
    };
}

#endif /* Time_hpp */
