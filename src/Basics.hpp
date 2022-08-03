#pragma once
#include "math.h"
#include "Coords.hpp"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))


template <typename T>
T max(T f, T s) noexcept{
    return MAX(f, s);
}

template <typename T>
T min(T f, T s) noexcept{
    return MIN(f, s);
}

double distance_pixels(const Coords &from, const Coords &to) noexcept;
void lerp(Coords &result, const Coords &from, const Coords &to, float progress);