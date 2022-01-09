#include "mt_main.hpp"

#ifdef MT_DEBUG
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#endif

int main(int argc, char * argv[]) {
#ifdef MT_DEBUG
if (catch_main(argc, argv)) return 1;
#endif
mt::MTAPP::run();
}
