#ifndef Timer_hpp
#define Timer_hpp

#include "mt.hpp"

namespace mt {
namespace util {

/// @class Timer
/// @brief countdown timer
class Timer {
public:
    virtual ~Timer() { }
    /// @param countdown value to start countdown from
    Timer(const uint64_t countdown = 0) : m_countdown(countdown) { }
    
    /// @return true if countdown has completed
    bool tick() {
        if (m_countdown) {
            return !m_countdown--;
        } else {
            return true;
        }
    }
    
    /// @param countdown value to start countdown from
    Timer & reset(const uint64_t countdown) {
        m_countdown = countdown;
        return *this;
    }

    /// @return remaining ticks in countdown
    uint64_t remaining() const {
        return m_countdown;
    }
    
private:
    uint64_t m_countdown;
};

}
}

#endif /* Timer_hpp */
