#ifndef SysTime_hpp
#define SysTime_hpp

#include "SysIncludes.hpp"

namespace mt {
namespace util {

/// @class SysTime
/// @brief interface for system time
class SysTime {
public:
    /// @brief uses current time
    SysTime();
    /// @brief specified time
    /// @param ms time since epoch time in milliseconds
    SysTime(uint64_t ms);
    
    /// @brief total milliseconds since epoch time
    uint64_t total_ms() const;
    
    
    /// @brief total seconds since epoch time
    uint64_t seconds() const;
    /// @brief total minutes since epoch time
    uint64_t minutes() const;
    /// @brief total hours since epoch time
    uint64_t hours() const;
    
    /// @brief timestamp as a string in format HH:MM:SS
    /// @param delim string that goes inbetween numbers in timestamp, default ":"
    string timestamp(string delim = ":") const;
    /// @brief datestamp as a string in format MM-DD-YYY
    /// @param delim string that goes inbetween numbers in datestamp, default "-"
    string datestamp(string delim = "-") const;
    
    /// @param t SysTime to add
    SysTime operator+(const SysTime & t) const;
    /// @param t SysTime to add
    SysTime & operator+=(const SysTime & t);
    /// @param t SysTime to add
    SysTime operator-(const SysTime & t) const;
    /// @param t SysTime to add
    SysTime & operator-=(const SysTime & t);
    
private:
    uint64_t m_ms; // milliseconds since epoch time
};

}
}

#endif /* Time_hpp */
