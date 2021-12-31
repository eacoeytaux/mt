#ifndef __Logger__
#define __Logger__

#include "SysIncludes.hpp"

namespace mt {
namespace util {

/// @brief type of message being logged
enum MESSAGE_TYPE {
    INFO_LOG = 0,
    WARNING_LOG,
    ERROR_LOG,
#ifdef MT_DEBUG
    DEBUG_LOG,
#endif
};

/// @class Logger
/// @brief interface for log messages
class Logger {
public:
    /// @brief initialization for Logger
    static void start();
    /// @brief de-initialization for Logger
    static void close();
    /// @brief print message to log file
    /// @param type type of message
    /// @param entry message
    static void print(MESSAGE_TYPE type, const char * entry, ...);
    // static void print(MESSAGE_TYPE type, const char * entry, const va_list & args);
    
private:
    /// @brief should never be constructed
    Logger() { }
};

}
}

#endif /* defined(__Logger__) */
