#pragma once
#include "../DrawingTool.hpp"

class MouseHighlightTool: public DrawingTool{
private:
    int mX, mY;
    float radius = 0.3;
    bool isMouseDown = false;
    int mdX, mdY;
protected:
    virtual void OnDraw() const noexcept override;
    virtual bool OnMouseMove(int x, int y) noexcept override; 
    virtual bool OnLMouseDown(int x, int y) noexcept override;
    virtual bool OnLMouseUp(int x, int y) noexcept override;
    virtual bool OnKeyDown(int vkCode, int repeat) noexcept override;
    virtual bool OnKeyUp(int vkCode) noexcept override;
    virtual bool OnTextInput(std::wstring str) noexcept override;
    virtual bool OnScrollUp() noexcept override;
    virtual bool OnScrollDown() noexcept override;
    
public:
    MouseHighlightTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg) noexcept;
};

