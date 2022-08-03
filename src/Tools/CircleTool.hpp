#pragma once

#include "PrimitiveTool.hpp"

class CircleTool: public PrimitiveTool{
protected:
    virtual void DrawPrimitive(const Coords &mouseDownCoord, const Coords &mouseUpCoord) const noexcept override;
public:
    CircleTool(int cx, int cy, const Texture &bg, const Texture &state, BrushTool &brush) noexcept;
};