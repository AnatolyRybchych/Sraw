#pragma once

class Coords{
private:
    double winX;
    double winY;

    int viewportCx;
    int viewportCy;
public:
    Coords(int viewportCx, int viewportCy) noexcept;
    float GetXGl() const noexcept;
    float GetYGl() const noexcept;
    int GetXWindows() const noexcept;
    int GetYWindows() const noexcept;
    float GetXGlPixels() const noexcept;
    float GetYGlPixels() const noexcept;

    void SetXGl(float x) noexcept;
    void SetYGl(float y) noexcept;
    void SetXWindows(int x) noexcept;
    void SetYWindows(int y) noexcept;
    void SetXGlPixels(float x) noexcept;
    void SetYGlPixels(float y) noexcept;  
    void SetViewport(int cx, int cy) noexcept;
};