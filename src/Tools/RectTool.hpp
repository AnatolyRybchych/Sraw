#pragma once
#include "RectOutlineTool.hpp"

class RectTool: public RectOutlineTool{
protected:
    virtual void DrawPrimitive(const Coords &mouseDownCoord, const Coords &mouseUpCoord) const noexcept override;
public:
    RectTool(int cx, int cy, const Texture &bg, const Texture &state, BrushTool &brush) noexcept;
};