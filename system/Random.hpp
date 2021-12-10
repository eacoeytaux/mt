#ifndef Random_hpp
#define Random_hpp

namespace mt {

class Angle;

class Random {
public:
    static void seed();
    static void seed(unsigned int seed);
    static bool r_bool(float true_odds = 0.5); // returns a boolean with true_odds chance of true and (1 - true_odds) chance of false
    static Angle r_Angle();
    static int r_int(int range);
    static int r_int(int low_bound, int high_bound);
    static float r_float(float range);
    static float r_float(float low_bound, float high_bound);
};

}

#endif /* Random_hpp */
