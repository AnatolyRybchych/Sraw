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
    DrawImage drawImage;
    int cx, cy;
public:
    const Texture &GetBackground() const noexcept;
    DrawingCanvas(Texture &bg);
    void OnShow(int cx, int cy);
    void Draw();
};
