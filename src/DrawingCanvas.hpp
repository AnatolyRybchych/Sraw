#pragma once
#include <memory>
#include "UnicodeWindows.hpp"
#include "DrawImage.hpp"
#include "Texture.hpp"
#include "Framebuffer.hpp"
#include <glad/glad.h>

class DrawingCanvas
{
private:
    Texture &bg;
    std::unique_ptr<Texture> currState = nullptr;
    Framebuffer frameBuffer;
    int cx, cy;
public:
    const Texture &GetBackground() const noexcept;
    DrawingCanvas(Texture &bg);
    bool OnMouseMove(int x, int y);
    bool OnLMouseDown(int x, int y);
    bool OnLMouseUp(int x, int y);
    void OnShow(int cx, int cy);
    void Draw();
};
