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
    static bool start(bool file = false);
    /// @brief de-initialization for Logger
    static bool close();
    /// @brief print message to log file
    /// @param type type of message
    /// @param entry message
    static bool log(MESSAGE_TYPE type, const char * entry, ...);
    /// @brief whether or not to print logs to console
    static bool print_to_console(bool b);
    
private:
    /// @brief should never be constructed
    Logger() { }
};

}
}

#endif /* defined(__Logger__) */
