#pragma once
#include <memory>
#include "UnicodeWindows.hpp"
#include "DrawImage.hpp"
#include "Tools/MouseHighlight.hpp"
#include "GlWrappers/Texture.hpp"
#include "GlWrappers/Framebuffer.hpp"
#include "DrawingTool.hpp"
#include "Tools/SelectMenuToolNode.hpp"
#include "SelectToolMenuManager.hpp"
#include <GL/glew.h>
#include "Quitable.hpp"

class DrawingCanvas: public CommitHandler
{
private:
    Texture &bg;
    Texture currState;
    SelectToolMenuManager toolMenuManager;
    Framebuffer frameBuffer;
    int cx, cy;
public:
    const Texture &GetBackground() const noexcept;
    DrawingCanvas(Texture &bg, Quitable &quitable, int cx, int cy);
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
    virtual void HandleCommit(std::function<void()> drawCommit) noexcept override;
};
