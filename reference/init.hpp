#ifndef INIT_HPP
#define INIT_HPP

#include "types.hpp"

#include <random>
#include <ctime>
#include <algorithm>

extern const void init_all() {
    srand(unsigned(time(NULL)));
    return;
}

#endif