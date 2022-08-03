#pragma once
#include "../DrawingTool.hpp"
#include "BrushTool.hpp"
#include "../Coords.hpp"

class PrimitiveTool: public DrawingTool{
private:
    static constexpr float previewSize = 0.2;
    static constexpr float previewOffset = 0.1;

    BrushTool &brush;

    bool isMouseDown;
    bool isAltDown;

    Coords lastMousePos;
    Coords p1;
    Coords p2;
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

    virtual void DrawPrimitive(const Coords &mouseDownCoord, const Coords &mouseUpCoord) const noexcept = 0;
public:
    PrimitiveTool(int cx, int cy, const Texture &bg, const Texture &state, BrushTool &brush) noexcept;

    const BrushTool &GetBrush() const noexcept;
};