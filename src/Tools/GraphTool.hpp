#pragma once

#include "PrimitiveTool.hpp"

class GraphTool: public PrimitiveTool{
    static constexpr float arrow_size = 0.03;
protected:
    virtual void DrawPrimitive(const Coords &mouseDownCoord, const Coords &mouseUpCoord) const noexcept override;
public:
    GraphTool(int cx, int cy, const Texture &bg, const Texture &state, BrushTool &brush) noexcept;
};