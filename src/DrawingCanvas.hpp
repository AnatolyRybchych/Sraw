#pragma once
#include <memory>
#include "UnicodeWindows.hpp"
#include "DrawImage.hpp"
#include "MouseHighlight.hpp"
#include "GlWrappers/Texture.hpp"
#include "GlWrappers/Framebuffer.hpp"
#include "DrawingTool.hpp"
#include "SelectMenuToolNode.hpp"
#include "SelectToolMenuManager.hpp"
#include <GL/glew.h>
#include "Quitable.hpp"
#include "DrawingTarget.hpp"

class DrawingCanvas{
private:
    Texture &bg;
    Texture currState;
    SelectToolMenuManager toolMenuManager;
    Framebuffer frameBuffer;
    int cx, cy;
public:
    const Texture &GetBackground() const noexcept;
    const Texture &GetCurrentState() const noexcept;
    DrawingCanvas(Texture &bg, Quitable &quitable, const DrawingTarget &drawingTarget, int cx, int cy);
    bool OnMouseMove(int x, int y);
    bool OnLMouseDown(int x, int y);
    bool OnLMouseUp(int x, int y);
    bool OnRMouseDown(int x, int y);
    bool OnRMouseUp(int x, int y);
    bool OnkeyDown(int vkCode, int repeat);
    bool Onkeyup(int vkCode);
    bool OnScrollUp() noexcept;
    bool OnScrollDown() noexcept;
    bool OnTextInput(std::wstring str);
    void Draw();
};
