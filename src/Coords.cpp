#include "Coords.hpp"

Coords::Coords(int viewportCx, int viewportCy) noexcept{
    this->viewportCx = viewportCx;
    this->viewportCy = viewportCy;
}

float Coords::GetXGl() const noexcept{
    return glX;
}

float Coords::GetYGl() const noexcept{
    return glY;
}

int Coords::GetXWindows() const noexcept{
    return (glX * 0.5 + 0.5) * viewportCx;
}

int Coords::GetYWindows() const noexcept{
    return (0.5 - glY * 0.5) * viewportCy;
}

float Coords::GetXGlPixels() const noexcept{
    return (glX * 0.5 + 0.5) * (float)viewportCx;
}

float Coords::GetYGlPixels() const noexcept{
    return (glY * 0.5 + 0.5) * (float)viewportCy;
}

void Coords::SetXGl(float x) noexcept{
    glX = x;
}

void Coords::SetYGl(float y) noexcept{
    glY = y;
}

void Coords::SetXWindows(int x) noexcept{
    glX = (x / (float)viewportCx) * 2.0 - 1.0;
}

void Coords::SetYWindows(int y) noexcept{
    glY = 1.0 - (y / (float)viewportCy) * 2.0;
}

void Coords::SetXGlPixels(float x) noexcept{
    glX = 2.0 * x / (float) viewportCx - 1.0;
}

void Coords::SetYGlPixels(float y) noexcept{
    glY = 2.0 * y / (float) viewportCy - 1.0;
}

void Coords::SetViewport(int cx, int cy) noexcept{
    viewportCx = cx;
    viewportCy = cy;
}

