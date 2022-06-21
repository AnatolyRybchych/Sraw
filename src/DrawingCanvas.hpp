#pragma once
#include <memory>
#include "UnicodeWindows.hpp"
#include "DrawImage.hpp"
#include "MouseHighlight.hpp"
#include "Texture.hpp"
#include "Framebuffer.hpp"
#include "DrawingTool.hpp"
#include "SelectMenuToolNode.hpp"
#include "SelectToolMenuManager.hpp"
#include <glad/glad.h>

class DrawingCanvas
{
private:
    Texture &bg;
    std::unique_ptr<Texture> currState = nullptr;
    SelectToolMenuManager toolMenuManager;
    Framebuffer frameBuffer;
    int cx, cy;
public:
    const Texture &GetBackground() const noexcept;
    DrawingCanvas(Texture &bg);
    bool OnMouseMove(int x, int y);
    bool OnLMouseDown(int x, int y);
    bool OnLMouseUp(int x, int y);
    bool OnRMouseDown(int x, int y);
    bool OnRMouseUp(int x, int y);
    void OnShow(int cx, int cy);
    bool OnkeyDown(int vkCode, int repeat);
    bool Onkeyup(int vkCode);
    bool OnScrollUp() noexcept;
    bool OnScrollDown() noexcept;
    bool OnTextInput(std::wstring str);
    void Draw();
};
