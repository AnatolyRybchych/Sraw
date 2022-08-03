#include "Basics.hpp"

double distance_pixels(const Coords &from, const Coords &to) noexcept{
    double x = from.GetXGlPixels() - to.GetXGlPixels();
    double y = from.GetYGlPixels() - to.GetYGlPixels();
    return sqrt(x*x + y*y);
}

void lerp(Coords &result, const Coords &from, const Coords &to, float progress){
    result.SetXGl(from.GetXGl() + (to.GetXGl() - from.GetXGl()) * progress);
    result.SetYGl(from.GetYGl() + (to.GetYGl() - from.GetYGl()) * progress);
}