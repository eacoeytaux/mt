#ifndef SysTime_hpp
#define SysTime_hpp

#include "mt.hpp"

namespace mt {
    class SysTime {
    public:
        SysTime();
        SysTime(uint64_t ms);
        
        uint64_t total_ms() const;
        
        uint64_t seconds() const;
        uint64_t minutes() const;
        uint64_t hours() const;
        
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
