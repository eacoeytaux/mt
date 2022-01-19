#ifndef Assert_hpp
#define Assert_hpp

#include "Debug.hpp"
#include "Logger.hpp"

namespace mt {
namespace util {

/// @class Assert
/// @brief used for code assertions
class Assert {
private:
    /// @brief universal check function
    /// @param b value to check
    /// @param message description of check
    /// @param args message string arguments
    /// @param quit exit code if false
    /// @return b
    static bool check(bool b, const char * message, const va_list & args, int quit = 0) {
        if (!b) {
            static int breakpoint = 0;
            if (breakpoint) { }
#ifdef MT_DEBUG
            Logger::log(ERROR_LOG, "assert failed! \"%s\"", message);
#endif
        }
        
        if (!b && strlen(message)) Logger::log(ERROR_LOG, message, args);
        assert(b);
        if (quit) exit(quit);
        return b;
    }
    
public:
    virtual ~Assert() { }
    Assert();
    
    /// @brief checks that must be true for code to run properly
    /// @param b value to check
    /// @param message description of check
    /// @return b
    static bool fatal(bool b, const char * message = "", ...) {
        va_list va_args;
        va_start(va_args, message);
        check(b, message, va_args);
        va_end(va_args);
        return b;
    }
    /// @brief non-fatal checks just for sanity
    /// @param b value to check
    /// @param message description of check
    /// @return b
    static bool soft(bool b, const char * message = "", ...) {
        va_list va_args;
        va_start(va_args, message);
        check(b, message, va_args);
        va_end(va_args);
        return b;
    }
    /// @brief debug check function
    /// @param b value to check
    /// @param message description of check
    /// @return b
    static bool debug(bool b, const char * message = "", ...) {
#ifdef MT_DEBUG
        va_list va_args;
        va_start(va_args, message);
        check(b, message, va_args);
        va_end(va_args);
#endif
        return b;
    }
    
    /// @brief asserts false where todos exist in code
    /// @param message description of check
    /// @return false
    static bool TODO(const char * message = "", ...) {
#ifdef MT_DEBUG
        va_list va_args;
        va_start(va_args, message);
        check(false, message, va_args);
        va_end(va_args);
#endif
        return false;
    }
};

}
}

#endif /* Assert_hpp */
