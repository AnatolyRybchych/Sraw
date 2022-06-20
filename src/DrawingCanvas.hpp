#pragma once
#include <memory>
#include "UnicodeWindows.hpp"
#include "DrawImage.hpp"
#include "MouseHighlight.hpp"
#include "Texture.hpp"
#include "Framebuffer.hpp"
#include "DrawingTool.hpp"
#include <glad/glad.h>

class DrawingCanvas
{
private:
    Texture &bg;
    std::unique_ptr<Texture> currState = nullptr;
    std::unique_ptr<DrawingTool> drawingTool = nullptr;
    Framebuffer frameBuffer;
    int cx, cy;
public:
    const Texture &GetBackground() const noexcept;
    DrawingCanvas(Texture &bg);
    void OnMouseMove(int x, int y);
    void OnLMouseDown(int x, int y);
    void OnLMouseUp(int x, int y);
    void OnShow(int cx, int cy);
    void OnkeyDown(int vkCode, int repeat);
    void Onkeyup(int vkCode);
    void OnScrollUp() noexcept;
    void OnScrollDown() noexcept;
    void OnTextInput(std::wstring str);
    void Draw();
};
