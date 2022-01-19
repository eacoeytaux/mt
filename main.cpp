#include "mtapp.hpp"
#include "mtest.hpp"

int main(int argc, char * argv[]) {
#ifdef MT_TEST
#include <iostream>
std::cout << "\nRUNNING CATCH TESTS" << std::endl;
if (catch_main(argc, argv)) return 1;
#endif
mt::mtapp::run();
}
