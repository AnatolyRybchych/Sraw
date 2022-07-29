#pragma once
#include "../DrawingTool.hpp"
#include "ColorPaletTool.hpp"

class TextTool: public DrawingTool{
private:
    static constexpr int MinFontSize = 18;
    static constexpr int MaxFontSize = 1000;
    static constexpr float FontIncrement = 0.1;

    float fontSize = 48;

    bool isMouseDown = false;
    bool isControlDown = false;

    int currX;
    int currY;

    void IncFontSize(bool dec) noexcept;

    std::wstring text = L"";
    ColorPaletTool &colorPalete;
protected://handlers should return true if requires to redraw
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
    TextTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg, ColorPaletTool &colorPalete) noexcept;
    std::wstring GetText() const noexcept;
};