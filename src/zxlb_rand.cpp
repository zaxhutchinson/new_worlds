#include"zxlb_rand.hpp"


namespace rnd {

    void InitRandom() {

        std::random_device rd;
        rng = RNG(rd());

    }

    int64_t d0N(int64_t N, int64_t num_dice) {
        int64_t total = 0;
        std::uniform_int_distribution<int64_t> d(0,N);
        for(int64_t i = 0; i < num_dice; i++) {
            total += d(rng);
        }
        return total;
    }

    int64_t d1N(int64_t N, int64_t num_dice) {
        int64_t total = 0;
        std::uniform_int_distribution<int64_t> d(1,N);
        for(int64_t i = 0; i < num_dice; i++) {
            total += d(rng);
        }
        return total;
    }

}