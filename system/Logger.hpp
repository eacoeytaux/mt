#ifndef __Logger__
#define __Logger__

namespace mt {
    enum MESSAGE_TYPE {
        INFO_LOG = 0,
        WARNING_LOG,
        ERROR_LOG,
#ifdef MT_DEBUG
        DEBUG_LOG,
#endif
    };
    
    class Logger {
    public:
        static void start();
        static void close();
        static void print(MESSAGE_TYPE type, const char * entry, ...);
//        static void print(MESSAGE_TYPE type, const char * entry, const va_list & args);
    };
}

#endif /* defined(__Logger__) */
