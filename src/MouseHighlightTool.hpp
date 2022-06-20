#pragma once
#include "DrawingTool.hpp"

class MouseHighlightTool: public DrawingTool{
private:
    int mX, mY;
    float radius = 0.3;
protected:
    virtual void OnDraw() const noexcept override;
    virtual void OnResize(int cx, int cy) noexcept override;
    virtual void OnMouseMove(int x, int y) noexcept override; 
    virtual void OnLMouseDown(int x, int y) noexcept override;
    virtual void OnLMouseUp(int x, int y) noexcept override;
    virtual void OnKeyDown(int vkCode, int repeat) noexcept override;
    virtual void OnKeyUp(int vkCode) noexcept override;
    virtual void OnTextInput(std::wstring str) noexcept override;
    virtual void OnScrollUp() noexcept override;
    virtual void OnScrollDown() noexcept override;
public:
    MouseHighlightTool(int cx, int cy) noexcept;
};

