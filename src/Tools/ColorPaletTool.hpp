#pragma once
#include "../DrawingTool.hpp"

class ColorPaletTool:public DrawingTool{
private:
    float r;
    float g;
    float b;
protected://handlers should return true if requires to redraw
    virtual void OnDraw() const noexcept override;
    virtual void OnDrawCommit() noexcept override;
    virtual void OnResize(int cx, int cy) noexcept override;
    virtual bool OnMouseMove(int x, int y) noexcept override; 
    virtual bool OnLMouseDown(int x, int y) noexcept override;
    virtual bool OnLMouseUp(int x, int y) noexcept override;
    virtual bool OnKeyDown(int vkCode, int repeat) noexcept override;
    virtual bool OnKeyUp(int vkCode) noexcept override;
    virtual bool OnTextInput(std::wstring str) noexcept override;
    virtual bool OnScrollUp() noexcept override;
    virtual bool OnScrollDown() noexcept override;
public:
    float GetRed() const noexcept;
    float GetGreen() const noexcept;
    float GetBlue() const noexcept;
    void SetRed(float value) noexcept;
    void SetGreen(float value) noexcept;
    void SetBlue(float value) noexcept;
    ColorPaletTool(int cx, int cy, CommitHandler &commitHandler) noexcept;
};