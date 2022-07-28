#include "Basics.hpp"

int lerpi(int from, int to, float progress) noexcept{
    return from + (to - from) * progress;
}

double distance2(double x1, double y1, double x2, double y2) noexcept{
    double x = x2 - x1;
    double y = y2 - y1;
    return sqrt(x*x + y*y);
}