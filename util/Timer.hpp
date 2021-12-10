#ifndef Timer_hpp
#define Timer_hpp

#include "mt.hpp"

namespace mt {

class Timer {
public:
    Timer(const uint64_t _countdown = 0) : m_countdown(_countdown) { }
    
    bool tick() {
        if (m_countdown) {
            return !m_countdown--;
        } else {
            return true;
        }
    }

    void reset(const uint64_t _countdown) {
        m_countdown = _countdown;
    }

    uint64_t remaining() const {
        return m_countdown;
    }
    
private:
    uint64_t m_countdown;
};

}

#endif /* Timer_hpp */
