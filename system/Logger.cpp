#include "mt.hpp"
#include "Logger.hpp"

#include <stdio.h>
#include <stdarg.h>
#include <sys/stat.h>

#include "SysTime.hpp"

using namespace mt;

bool init = false;
FILE * log_file;

// TODO none of this works :(

void Logger::start() {
    log_file = fopen(("logs/" + SysTime().timestamp(".") + "." + SysTime().datestamp(".") + ".log").c_str(), "w+");
    print(INFO_LOG, "starting ........ ( v%s )", VERSION);
    init = true;
}

void Logger::print(MESSAGE_TYPE _type, const char * _entry, ...) {
    if (!init) return;
    
//    va_list va_args;
//    va_start(va_args, _entry);
//    print(_type, _va_args);
//    va_end(va_args);
//}
//
//void Logger::print(MESSAGE_TYPE _type, const char * _entry, va_list _va_args) {
    if (!init) return;
    
    SysTime current;
    
    char* type_str = new char[8];

    switch (_type) {
        case WARNING_LOG:
            type_str = (char*)"WARNING";
            break;
        case ERROR_LOG:
            type_str = (char*)"ERROR";
            break;
#ifdef MT_DEBUG
        case DEBUG_LOG:
            type_str = (char*)"DEBUG";
            break;
#endif
        case INFO_LOG:
        default:
            type_str = (char*)"INFO";
            break;
    }

//    fprintf(log_file, "[%s] [%s] ", current.timestamp().c_str(), type_str);
//    vfprintf(log_file, _entry, _va_args); // TODO
//    fprintf(log_file, "\n");
//    fflush(log_file);
}

void Logger::close() {
    print(INFO_LOG, "complete ........");
    fclose(log_file);
    init = false;
}
