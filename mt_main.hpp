#ifndef mt_main_hpp
#define mt_main_hpp

#include "mt.hpp"

namespace mt {

class MTROGUE {
public:
    static void run();
    static void shutdown(int exitcode = 0);
};

}

#endif /* mt_main_hpp */
