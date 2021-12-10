#include "SysTime.hpp"

#include <ctime>

using namespace mt;

SysTime::SysTime() :
m_ms(std::chrono::system_clock::now().time_since_epoch().count() / 1000) { }

SysTime::SysTime(uint64_t _ms) :
m_ms(_ms) { }

uint64_t SysTime::total_ms() const {
    return m_ms;
}

uint64_t SysTime::seconds() const {
    return (m_ms / 1000);
}

uint64_t SysTime::minutes() const {
    return (m_ms / (1000 * 60));
}
    
uint64_t SysTime::hours() const {
    return (m_ms / (1000 * 60 * 60));
}

string SysTime::timestamp(string _delim) const {
    char time_str[9];
    time_t time = m_ms / 1000;
    tm * ptm = localtime(&time);
    strftime(time_str, sizeof(time_str), ("%H" + _delim + "%M" + _delim + "%S").c_str(), ptm);
    return string(time_str);
}

string SysTime::datestamp(string _delim) const {
    char time_str[11];
    time_t time = m_ms / 1000;
    tm * ptm = localtime(&time);
    strftime(time_str, sizeof(time_str), ("%m" + _delim + "%d" + _delim + "%Y").c_str(), ptm);
    return string(time_str);
}

SysTime SysTime::operator+(const SysTime & _t) const {
    return SysTime(m_ms + _t.m_ms);
}

SysTime & SysTime::operator+=(const SysTime & _t) {
    m_ms += _t.m_ms;
    return *this;
}

SysTime SysTime::operator-(const SysTime & _t) const {
    return SysTime(m_ms - _t.m_ms);
}

SysTime & SysTime::operator-=(const SysTime & _t) {
    m_ms -= _t.m_ms;
    return *this;
}
