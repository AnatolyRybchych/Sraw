#include "Coords.hpp"

Coords::Coords(int viewportCx, int viewportCy) noexcept{
    this->viewportCx = viewportCx;
    this->viewportCy = viewportCy;
}

double Coords::GetXGl() const noexcept{
    return 2.0 * winX / (double)viewportCx  - 1.0;
}

double Coords::GetYGl() const noexcept{
    return 1.0 - 2.0 * winY / (double)viewportCy;
}

int Coords::GetXWindows() const noexcept{
    return winX;
}

int Coords::GetYWindows() const noexcept{
    return winY;
}

double Coords::GetXGlPixels() const noexcept{
    return winX;
}

double Coords::GetYGlPixels() const noexcept{
    return viewportCy - winY;
}

void Coords::SetXGl(double x) noexcept{
    winX = (x * 0.5 + 0.5) * (double)viewportCx;
}

void Coords::SetYGl(double y) noexcept{
    winY = (0.5 - y * 0.5) * (double)viewportCy;
}

void Coords::SetXWindows(int x) noexcept{
    winX = x;
}

void Coords::SetYWindows(int y) noexcept{
    winY = y;
}

void Coords::SetXGlPixels(double x) noexcept{
    winX = x;
}

void Coords::SetYGlPixels(double y) noexcept{
    winY = viewportCy - y;
}

void Coords::SetViewport(int cx, int cy) noexcept{
    viewportCx = cx;
    viewportCy = cy;
}

