#include "mt.hpp"
#include "Logger.hpp"

#include <stdio.h>
#include <stdarg.h>
#include <sys/stat.h>

#include "SysTime.hpp"

#define LOG_DIRECTORY "logs/"

using namespace mt;

bool init = false;
bool file = false;
bool console = true;
FILE * log_file;

bool Logger::start(const bool _file) {
    file = _file;
    init = false;
    if (file) log_file = fopen((LOG_DIRECTORY + SysTime().timestamp(".") + "." + SysTime().datestamp(".") + ".log").c_str(), "w+");
    log(INFO_LOG, "\n--------------------------------\n");
    log(INFO_LOG, "starting ........ ( v%s )", VERSION);
    if (!file || log_file) init = true;
    return init;
}

bool Logger::log(MESSAGE_TYPE _type, const char * _entry, ...) {
    try {
        va_list va_args;
        va_start(va_args, _entry);
        
        SysTime current;
        
        bool type = true;
        char* type_str ; // = new char[8];
        switch (_type) {
            case INFO_LOG:
                type = true;
                type_str = (char*)"INFO";
                break;
            case WARNING_LOG:
                type = true;
                type_str = (char*)"WARNING";
                break;
            case ERROR_LOG:
                type = true;
                type_str = (char*)"ERROR";
                break;
    #ifdef MT_DEBUG
            case DEBUG_LOG:
                type = true;
                type_str = (char*)"DEBUG";
                break;
    #endif
            default:
                type = false;
                type_str = (char*)"";
                break;
        }
        
        if (console) {
            vprintf(_entry, va_args);
            printf("\n");
        }
        
        if (file) {
            fprintf(log_file, "[%s] ", current.timestamp().c_str());
            if (type) fprintf(log_file, "[%s] ", type_str);
            vfprintf(log_file, _entry, va_args);
            fprintf(log_file, "\n");
            fflush(log_file);
        }
        
        va_end(va_args);
    } catch (exception e) {
        cout << e.what() << endl;
        return false;
    }
    
    return init;
}

bool Logger::print_to_console(const bool b) {
    console = b;
    return true;
}

bool Logger::close() {
    init = false;
    log(INFO_LOG, "complete ............");
    log(INFO_LOG, "\n--------------------------------\n");
    fclose(log_file);
    return init;
}
