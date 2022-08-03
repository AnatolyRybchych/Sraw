#include "RectOutlineTool.hpp"

void RectOutlineTool::DrawPrimitive(const Coords &mouseDownCoord, const Coords &mouseUpCoord) const noexcept{
    Coords p1 = mouseDownCoord;
    Coords p2 = mouseDownCoord;
    p2.SetXGlPixels(mouseUpCoord.GetXGlPixels());
    Coords p3 = mouseDownCoord;
    p3.SetYGlPixels(mouseUpCoord.GetYGlPixels());
    Coords p4 = mouseUpCoord;

    GetBrush().DrawLine(p1, p2);
    GetBrush().DrawLine(p4, p2);
    GetBrush().DrawLine(p1, p3);
    GetBrush().DrawLine(p4, p3);
};

RectOutlineTool::RectOutlineTool(int cx, int cy, const Texture &bg, const Texture &state, BrushTool &brush) noexcept
:PrimitiveTool(cx, cy, bg, state, brush){

};