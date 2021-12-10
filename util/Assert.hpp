#ifndef Assert_hpp
#define Assert_hpp

#include "Debug.hpp"
#include "Logger.hpp"
#include "UtilFunc.hpp"

namespace mt {

class Assert {
private:
    static bool check(bool b, const char * message, const va_list & args, int quit = 0) {
        if (!b) {
            static int breakpoint = 0;
            if (breakpoint) { }
#ifdef MT_DEBUG
            cout << "assert failed!" << endl;
#endif
        }
        
        if (!b && strlen(message)) Logger::print(ERROR_LOG, message, args);
        assert(b);
        if (quit) exit(quit);
        return b;
    }
    
public:
    virtual ~Assert() { } // TODO apply to all ugh
    Assert();
    
    static bool fatal(bool b, const char * message = "", ...) {
        va_list va_args;
        va_start(va_args, message);
        check(b, message, va_args);
        va_end(va_args);
        return b;
    }
    static bool soft(bool b, const char * message = "", ...) {
        va_list va_args;
        va_start(va_args, message);
        check(b, message, va_args);
        va_end(va_args);
        return b;
    }
    static bool debug(bool b, const char * message = "", ...) {
#ifdef MT_DEBUG
        va_list va_args;
        va_start(va_args, message);
        check(b, message, va_args);
        va_end(va_args);
#endif
        return b;
    }
};
}

#endif /* Assert_hpp */
