#pragma once

class Coords{
private:
    double winX;
    double winY;

    int viewportCx;
    int viewportCy;
public:
    Coords(int viewportCx, int viewportCy) noexcept;
    double GetXGl() const noexcept;
    double GetYGl() const noexcept;
    int GetXWindows() const noexcept;
    int GetYWindows() const noexcept;
    double GetXGlPixels() const noexcept;
    double GetYGlPixels() const noexcept;

    void SetXGl(double x) noexcept;
    void SetYGl(double y) noexcept;
    void SetXWindows(int x) noexcept;
    void SetYWindows(int y) noexcept;
    void SetXGlPixels(double x) noexcept;
    void SetYGlPixels(double y) noexcept;  
    void SetViewport(int cx, int cy) noexcept;
};