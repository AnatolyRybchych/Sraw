#include "GraphTool.hpp"

void GraphTool::DrawPrimitive(const Coords &mouseDownCoord, const Coords &mouseUpCoord) const noexcept{
    double cx = mouseDownCoord.GetXGlPixels() - mouseUpCoord.GetXGlPixels();
    double cy = mouseDownCoord.GetYGlPixels() - mouseUpCoord.GetYGlPixels();
    Coords _p1 = mouseDownCoord;
    Coords _p2 = mouseUpCoord;

    _p1.SetXGlPixels(mouseDownCoord.GetXGlPixels()  - (cx * (1.0 - 1.0)));
    _p1.SetYGlPixels(mouseDownCoord.GetYGlPixels()  - (cy * (1.0 - 0.5)));
    _p2.SetXGlPixels(mouseDownCoord.GetXGlPixels()  - (cx * (1.0 - 0.0)));
    _p2.SetYGlPixels(mouseDownCoord.GetYGlPixels()  - (cy * (1.0 - 0.5)));
    GetBrush().DrawLine(_p1, _p2);

    _p1.SetXGlPixels(mouseDownCoord.GetXGlPixels()  - (cx * (1.0 - 0.5)));
    _p1.SetYGlPixels(mouseDownCoord.GetYGlPixels()  - (cy * (1.0 - 1.0)));
    _p2.SetXGlPixels(mouseDownCoord.GetXGlPixels()  - (cx * (1.0 - 0.5)));
    _p2.SetYGlPixels(mouseDownCoord.GetYGlPixels()  - (cy * (1.0 - 0.0)));
    GetBrush().DrawLine(_p1, _p2);

    _p1.SetXGlPixels(mouseDownCoord.GetXGlPixels()  - (cx * (1.0 - (0.5 + arrow_size))));
    _p1.SetYGlPixels(mouseDownCoord.GetYGlPixels()  - (cy * (1.0 - (1.0 - arrow_size))));
    _p2.SetXGlPixels(mouseDownCoord.GetXGlPixels()  - (cx * (1.0 - 0.5)));
    _p2.SetYGlPixels(mouseDownCoord.GetYGlPixels()  - (cy * (1.0 - 1.0)));
    GetBrush().DrawLine(_p1, _p2);

    _p1.SetXGlPixels(mouseDownCoord.GetXGlPixels()  - (cx * (1.0 - (0.5 - arrow_size))));
    GetBrush().DrawLine(_p1, _p2);

    _p1.SetXGlPixels(mouseDownCoord.GetXGlPixels()  - (cx * (1.0 - arrow_size)));
    _p1.SetYGlPixels(mouseDownCoord.GetYGlPixels()  - (cy * (1.0 - (0.5 - arrow_size))));
    _p2.SetXGlPixels(mouseDownCoord.GetXGlPixels()  - (cx * (1.0 - 0.0)));
    _p2.SetYGlPixels(mouseDownCoord.GetYGlPixels()  - (cy * (1.0 - 0.5)));
    GetBrush().DrawLine(_p1, _p2);

    _p1.SetYGlPixels(mouseDownCoord.GetYGlPixels()  - (cy * (1.0 - (0.5 + arrow_size))));
    GetBrush().DrawLine(_p1, _p2);
}

GraphTool::GraphTool(int cx, int cy, const Texture &bg, const Texture &state, BrushTool &brush) noexcept
:PrimitiveTool(cx, cy, bg, state, brush){

};