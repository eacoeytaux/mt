#include "mt.hpp"
#include "Random.hpp"

#include "Logger.hpp"
#include "SysTime.hpp"
#include "Angle.hpp"

NAMESPACES
using mt::util::Random;

void Random::seed() {
    seed((int)(SysTime().total_ms() * SysTime().total_ms() * SysTime().total_ms()));
}

void Random::seed(const unsigned int _seed) {
    std::srand(_seed);
//    Logger::print(INFO_, "random seed ..... ( %u )", seed);
//    cout << "random seed ..... ( " << seed << " )" << endl;
}

bool Random::r_bool(const float _true_odds) {
    Assert::soft(_true_odds >= 0 && _true_odds <= 1, "incorrect bounds");
    
    if (_true_odds >= 1)
        return true;
    else if (_true_odds <= 0)
        return false;
    
    return (r_float(1.0) <= _true_odds);
}

Angle Random::r_Angle() {
    return Angle(r_float(PI * 2));
}

int Random::r_int(const int _range) {
    if (_range) return (rand() % _range);
    else return 0;
}

int Random::r_int(const int _low_bound, const int _high_bound) {
    Assert::soft(_high_bound >= _low_bound, "incorrect bounds");
    return Random::r_int(_high_bound - _low_bound) + _low_bound;
}

float Random::r_float(const float _range) {
    return ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * _range);
}

float Random::r_float(const float _low_bound, const float _high_bound) {
    Assert::soft(_high_bound >= _low_bound, "incorrect bounds");
    return r_float(_high_bound - _low_bound) + _low_bound;
}
